#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <strings.h>
#include "files.h"
#include "playlist.h"
#include "cue_sheet_file.h"
#include "libcue/libcue.h"

#define FRAMES_PER_SECOND (75)

int load_cue_sheet(struct plist *plist, char *cwd, const char *file, int *error_flag)
{
#ifndef HAVE_CUE
   *error_flag = ERROR_NOT_SUPPORTED;
   return -1; 
#else
   FILE *fcue = NULL;
   Cd *cd = NULL;
   
   fcue = fopen (file, "r");
   if (!fcue)
   {
      *error_flag = ERROR_NO_STAT;
      goto error;
   }

   cd = cue_parse_file (fcue);
   fclose (fcue); fcue = NULL;
   if (!cd)
   {
      *error_flag = ERROR_PARSE;
      goto error;
   }

   int ntracks = cd_get_ntrack (cd);
   Cdtext *cd_cdtext = cd_get_cdtext (cd);
   int i;
   for (i = 0; i < ntracks; i++)
   {
      /* Retrieve CUE metadata from libcue */
      Track *track = cd_get_track (cd, i+1);
      if (!track)
      {
         *error_flag = ERROR_PARSE;
         goto error;
      }

      const char *filename = track_get_filename (track);
      if (!filename)
      {
         *error_flag = ERROR_PARSE;
         goto error;
      }
      char full_path[PATH_MAX];
      snprintf (full_path, PATH_MAX, "%s/%s", cwd, filename);

      time_t stime = track_get_start (track) / FRAMES_PER_SECOND;
      time_t etime = stime + track_get_length (track) / FRAMES_PER_SECOND;

      Cdtext *track_cdtext = track_get_cdtext (track);

      struct file_tags tags = {0};
      char *val;

      val = cdtext_get (PTI_TITLE, cd_cdtext);
      if (val) tags.album = val;

      val = cdtext_get (PTI_TITLE, track_cdtext);
      if (val) tags.title = val;

      /* Album artist */
      val = cdtext_get (PTI_PERFORMER, cd_cdtext);
      if (val) tags.artist = val;

      /* Track artist trumps album artist */
      val = cdtext_get (PTI_PERFORMER, track_cdtext);
      if (val) tags.artist = val;

      tags.track = i+1;
      tags.time = etime - stime;
      tags.filled = TAGS_TIME;
      if (tags.title || tags.artist || tags.album)
         tags.filled |= TAGS_COMMENTS;

      /* Now add the playlist entry and set the tags */
      int plist_i = plist_add (plist, full_path);

      plist_set_cue (plist, plist_i, stime, etime, tags.title, full_path);
      plist_set_tags (plist, plist_i, &tags);
   }

   cd_delete (cd);

   return ntracks;

error:
   if (cd) cd_delete (cd);
   return -1;
#endif
}

bool is_cue_track(const struct plist *playlist, int index)
{
#ifndef HAVE_CUE
    return false;
#else
    return playlist->items[index].type == F_CUE_TRACK;
#endif
}

bool is_cue_sheet_file(const char *file)
{
#ifndef HAVE_CUE
    return false;
#else
    const char *ext = ext_pos (file);

    if (ext && (!strcasecmp(ext, "cue") || !strcasecmp(ext, "CUE")))
        return true;

    return false;
#endif
}
