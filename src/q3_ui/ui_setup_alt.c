/*
 * ui_setup_alt.c
 *
 * (Partically based on ui_playermodel.c)
 */

#include "ui_local.h"

#define SETUP_MENU_VERTICAL_SPACING		24
//#define PLAYERGRID_COLS		3
//#define PLAYERGRID_ROWS		1
#define MAX_CLASS		3

#define ART_BACK0	"menu/art/back_0"
#define ART_BACK1	"menu/art/back_1"	
#define ART_FRAMEL	"menu/art/frame2_l"
#define ART_FRAMER	"menu/art/frame1_r"

#define ID_BACK			10
#define ID_DEFAULTCLASS		11

typedef struct {
	menuframework_s		menu;

	menubitmap_s		framel;
	menubitmap_s		framer;

	menutext_s		banner;

	menubitmap_s		pics[MAX_CLASS];
	menubitmap_s		picbuttons[MAX_CLASS];

	menutext_s		classname;
	menubitmap_s		back;

	int			nummodels;
	char			modelnames[MAX_CLASS][128];
	char			modelskin[64];
	int			selectedclassindex;
	char			selectedclass[64];
} setupAlt_t;

static setupAlt_t s_setupAlt;

//trap_Cvar_Set("changeclass", s_setupAlt.selectedclass);

/*
 * UI_SetupAlt_MenuEvent
 */
static void UI_SetupAlt_MenuEvent(void *ptr, int event)
{
	if (event != QM_ACTIVATED)
		return;

	switch (((menucommon_s *)ptr)->id) {
	case ID_BACK:
		UI_PopMenu();
		break;
	}
}

/*
 * UI_SetupAlt_PicEvent
 */
static void UI_SetupAlt_PicEvent(void *ptr, int event)
{
	int	i;

	if (event != QM_ACTIVATED)
		return;

	for (i=0; i<MAX_CLASS; i++) {
		// reset
 		s_setupAlt.pics[i].generic.flags       &= ~QMF_HIGHLIGHT;
 		s_setupAlt.picbuttons[i].generic.flags |= QMF_PULSEIFFOCUS;
	}

	// set selected
	i = ((menucommon_s*)ptr)->id;
	s_setupAlt.pics[i].generic.flags       |= QMF_HIGHLIGHT;
	s_setupAlt.picbuttons[i].generic.flags &= ~QMF_PULSEIFFOCUS;

	// get model and strip icon
	// TODO
	/************************************************************
	modelnum = s_setupAlt. + i;
	buffptr  = s_playermodel.modelnames[modelnum] + strlen("models/players/");
	pdest    = strstr(buffptr,"icon_");
	if (pdest) {
		// track the whole model/skin name
		Q_strncpyz(s_playermodel.modelskin,buffptr,pdest-buffptr+1);
		strcat(s_playermodel.modelskin,pdest + 5);

		// separate the model name
		maxlen = pdest-buffptr;
		if (maxlen > 16)
			maxlen = 16;
		Q_strncpyz( s_playermodel.modelname.string, buffptr, maxlen );
		Q_strupr( s_playermodel.modelname.string );

		// separate the skin name
		maxlen = strlen(pdest+5)+1;
		if (maxlen > 16)
			maxlen = 16;
		Q_strncpyz( s_playermodel.skinname.string, pdest+5, maxlen );
		Q_strupr( s_playermodel.skinname.string );

		s_playermodel.selectedmodel = modelnum;

		if( trap_MemoryRemaining() > LOW_MEMORY ) {
			PlayerModel_UpdateModel();
		}
	}
	// *************************************************************/
}

/*
 * UI_SetupAlt_Cache
 */
static void UI_SetupAlt_Cache(void)
{
	// TODO
}

/*
 * UI_SetupAlt_MenuInit
 */
// TODO
static void UI_SetupAlt_MenuInit(void)
{
	UI_SetupAlt_Cache();

	memset( &s_setupAlt, 0, sizeof(setupAlt_t) );

	s_setupAlt.menu.wrapAround 	= qtrue;
	s_setupAlt.menu.fullscreen 	= qtrue;

	s_setupAlt.banner.generic.type 	= MTYPE_BTEXT;
	s_setupAlt.banner.generic.x 	= 320;
	s_setupAlt.banner.generic.y 	= 16;
	s_setupAlt.banner.string	= "NT SETUPS";
	s_setupAlt.banner.style		= UI_CENTER;

}

/*
 * UI_SetupAltMenu
 */
void UI_SetupAltMenu(void)
{
	UI_SetupAlt_MenuInit();
	UI_PushMenu( &s_setupAlt.menu );
}

