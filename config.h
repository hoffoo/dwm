/* See LICENSE file for copyright and license details. */
#include "xkbcommon/xkbcommon-keysyms.h"

/* appearance */
static const char *fonts[] = {
    "fixed:size=12"
};
static const char dmenufont[]       = "fixed:size=10";

static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#8B0000";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */


static void keysh(const Arg *arg);

#define NUMCOLORS         4
#define MAXCOLORS         3
static const char *colors[][3] = {
  /*               fg         bg         border   */
  [SchemeNorm] = { "#bbbbbb", "#222222", "#444444" },  // normal
  [SchemeSel]  = { "#eeeeee", "#005577", "#8B0000" },  // selected
  /*
  { "#ff0000", "#000000", "#ffff00" },  // urgent/warning  (black on yellow)
  { "#ff0000", "#ffffff", "#ff0000" },  // error
  // add more here
  */
};

/* tagging */
#define MAX_TAGNAME_LEN 14		/* excludes TAG_PREPEND */
#define TAG_PREPEND "%1i:"		/* formatted as 2 chars */
#define MAX_TAGLEN 16			/* altogether */
static char tags[][MAX_TAGLEN] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class         instance    title       tags mask     isfloating   monitor */
	{ "Steam",       NULL,       NULL,       0,            True,        -1 },
	{ "Zoom",        NULL,       NULL,       0,            True,        -1 },
	{ "Leafpad",     NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, "-l", "15", NULL };
/* static const char *termcmd[]  = { "/usr/bin/urxvt", "-fn", "xft:Inconsolata:size=13:antialias=true:hinting=true", "-fb", "xft:Inconsolata:size=13:antialias=true:hinting=true", NULL }; */
static const char *termcmd[]  = { "/usr/bin/urxvt", NULL };
static const char *browsercmd[]  = { "/usr/bin/firefox", NULL };
static const char *xscreensavercmd[]  = { "/usr/bin/xscreensaver-command", "-lock", NULL };
static const char *dunstclosecmd[]  = { "/usr/bin/dunstctl", "close-all", NULL };

/* path to keysh script */
#define keyshpath "/home/marin/.keysh"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
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
    { MODKEY,                       XK_s,      togglecanfocusfloating,   {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      nametag,        {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { ControlMask,                  XK_Super_L,  spawn,        {.v = browsercmd } },
    { ControlMask,                  XK_space,  spawn,        {.v = dunstclosecmd } },
    { 0,                            XK_Super_L,  spawn,         {.v = termcmd } },
    { MODKEY|ControlMask,           XK_l,        spawn,        {.v = xscreensavercmd } },
    { 0,                            XKB_KEY_XF86MonBrightnessUp,       keysh, {0} },
    { 0,                            XKB_KEY_XF86MonBrightnessDown,     keysh, {0} },
    { 0,                            XKB_KEY_XF86AudioPrev,             keysh, {0} },
    { 0,                            XKB_KEY_XF86AudioPlay,             keysh, {0} },
    { 0,                            XKB_KEY_XF86AudioNext,             keysh, {0} },
    { 0,                            XKB_KEY_XF86AudioMute,             keysh, {0} },
    { 0,                            XKB_KEY_XF86AudioLowerVolume,      keysh, {0} },
    { 0,                            XKB_KEY_XF86AudioRaiseVolume,      keysh, {0} },
    { 0,                            XK_F5,                     keysh, {0} },
    { 0,                            XK_F6,                     keysh, {0} },
    { 0,                            XK_F7,                     keysh, {0} },
    { 0,                            XK_F8,                     keysh, {0} },
    { 0,                            XK_F9,                     keysh, {0} },
    { 0,                            XK_F10,                    keysh, {0} },
    { 0,                            XKB_KEY_XF86PowerOff,              keysh, {0} },
    { 0,                            XKB_KEY_Print,             keysh, {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

