/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { 
	"Dina:size=9", 
	"Siji:style=Regular",
	"monospace:size=10",
};
/* static const char dmenufont[]       = "Cascadia Code:size=10"; */
static const char dmenufont[]       = "Dina:size=10";
static const char col_gray1[]       = "#161821"; /* bar BG */
static const char col_gray2[]       = "#161821"; /* unfocused border */
static const char col_gray3[]       = "#c6c8d1"; /* tags text */
static const char col_gray4[]       = "#c6c8d1"; /* window text */
static const char col_cyan[]        = "#a093c7"; /* focused window border */
static const char col_yell[]        = "#ebcb8b";
static const char col_redd[]        = "#e27878";
static const char col_gree[]        = "#b4be82";
static const char col_oran[]        = "#e2a478";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_cyan, col_gray1, col_cyan  },
};

/* tagging */
/* static const char *tags[] = { */
/* 	"\ue010", */
/* 	"\ue011", */
/* 	"\ue012", */
/* 	"\ue013", */
/* 	"\ue014", */
/* }; */
static const char *tags[] = {
	"1",
	"10",
	"11",
	"100",
	"101",
	"111",
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{ "Navigator",          "firefox",  NULL,       1 << 1,       0,           -1 },
	{ "TelegramDesktop",  NULL,       NULL,       1 << 4,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "gaplessgrid.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\ue002",      tile },    /* first entry is default */
	{ "\ue027",      NULL },    /* no layout function means floating behavior */
	{ "\ue000",      monocle },
 	{ "\ue008",      spiral },
 	{ "\ue007",      dwindle },
	{ "\ue005",      gaplessgrid },
	{ "\ue003",      bstack },
	{ "\ue004",      bstackhoriz },
	{ "\ue001",      centeredmaster },
	{ "\ue024",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon,"-nb", col_gray1, "-nf", col_gray4, "-sb", col_oran, "-sf", col_gray1, NULL };
static const char *ttftermcmd[] = { "st", "-f", "Cascadia Code:style=Regular:size=12", NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *stabbedcmd[] = { "tabbed", "-c", "st", "-w", NULL };
static const char *srftbedcmd[] = { "tabbed", "-c", "surf", "-e", NULL };
static const char *nnnfmcmd[]   = { "st", "-t", "3n", "-e", "nnn", NULL };
static const char *pythncmd[]   = { "st", "-t", "calq", "-e", "python", "-q", NULL };
static const char *slockcmd[]   = { "slock", NULL };
static const char *dsplycmd[]   = { "monitor", NULL };
static const char *srshtcmd[]   = { "out", NULL };
static const char *sshotcmd[]   = { "mshot", NULL };
static const char *backgcmd[]   = { "walp", NULL };
static const char *downvol[]    = { "amixer", "set", "Master", "2-", NULL };
static const char *upvol[]      = { "amixer", "set", "Master", "2+", NULL };
static const char *mute[]       = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *pplpa[]      = { "playerctl", "-a", "play-pause", NULL };
static const char *pstop[]      = { "playerctl", "-a", "stop", NULL };
static const char *pnext[]      = { "playerctl", "-a", "next", NULL };
static const char *pprev[]      = { "playerctl", "-a", "previous", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_e,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_c,      spawn,          {.v = ttftermcmd } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = stabbedcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = nnnfmcmd} },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = srftbedcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = pythncmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slockcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dsplycmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = srshtcmd } },
	{ MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = pplpa } },
	{ MODKEY,                       XK_Down,   spawn,          {.v = downvol } },
	{ MODKEY,                       XK_Up,     spawn,          {.v = upvol } },
	{ MODKEY,                       XK_Left,   spawn,          {.v = pprev } },
	{ MODKEY,                       XK_Right,  spawn,          {.v = pnext } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = backgcmd } },
	{ 0,                           0x1008FF2d, spawn,          {.v = slockcmd } },
	{ 0,                           0x1008FF11, spawn,          {.v = downvol } },
	{ 0,                           0x1008FF59, spawn,          {.v = dsplycmd } },
	{ 0,                           0xff61,     spawn,          {.v = sshotcmd } },
	{ 0,                           0x1008FF17, spawn,          {.v = pnext } },
	{ 0,                           0x1008FF15, spawn,          {.v = pstop } },
	{ 0,                           0x1008FF16, spawn,          {.v = pprev } },
	{ 0,                           0x1008FF12, spawn,          {.v = mute } },
	{ 0,                           0x1008FF13, spawn,          {.v = upvol } },
	{ 0,                           0x1008FF14, spawn,          {.v = pplpa } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
        { MODKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[4]} },
        { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} },
        { MODKEY,                       XK_v,      setlayout,      {.v = &layouts[6]} },
        { MODKEY|ShiftMask,             XK_v,      setlayout,      {.v = &layouts[7]} },
        { MODKEY,                       XK_z,      setlayout,      {.v = &layouts[8]} },
        { MODKEY|ShiftMask,             XK_z,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_a,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_7,                      3)
	TAGKEYS(                        XK_8,                      4)
	TAGKEYS(                        XK_9,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = srshtcmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

