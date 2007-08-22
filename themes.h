#ifndef THEMES_H
#define THEMES_H

enum color_index
{
	CLR_BACKGROUND,
	CLR_FRAME,
	CLR_WIN_TITLE,
	CLR_MENU_ITEM_DIR,
	CLR_MENU_ITEM_DIR_SELECTED,
	CLR_MENU_ITEM_PLAYLIST,
	CLR_MENU_ITEM_PLAYLIST_SELECTED,
	CLR_MENU_ITEM_FILE,
	CLR_MENU_ITEM_FILE_SELECTED,
	CLR_MENU_ITEM_FILE_MARKED,
	CLR_MENU_ITEM_FILE_MARKED_SELECTED,
	CLR_MENU_ITEM_INFO,
	CLR_MENU_ITEM_INFO_SELECTED,
	CLR_MENU_ITEM_INFO_MARKED,
	CLR_MENU_ITEM_INFO_MARKED_SELECTED,
	CLR_STATUS,
	CLR_TITLE,
	CLR_STATE,
	CLR_TIME_CURRENT,
	CLR_TIME_LEFT,
	CLR_TIME_TOTAL,
	CLR_TIME_TOTAL_FRAMES,
	CLR_SOUND_PARAMS,
	CLR_LEGEND,
	CLR_INFO_DISABLED,
	CLR_INFO_ENABLED,
	CLR_MIXER_BAR_EMPTY,
	CLR_MIXER_BAR_FILL,
	CLR_TIME_BAR_EMPTY,
	CLR_TIME_BAR_FILL,
	CLR_ENTRY,
	CLR_ENTRY_TITLE,
	CLR_ERROR,
	CLR_MESSAGE,
	CLR_PLIST_TIME,
	CLR_LAST, /* Fake element to get number of collors */
	CLR_WRONG
};

void theme_init (const int has_xterm);
int get_color (const enum color_index);
void themes_switch_theme (const char *file);

#endif
