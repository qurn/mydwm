/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "dejavu:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char sol_base00[]      = "#657b83"; /*was #bbbbbb, bright grey*/
static const char sol_cybri[]       = "#2aa198"; /*was #eeeeee, white*/
static const char sol_base03[]      = "#002b36"; /*Solarized dark background, was "#005577"*/
static const char sol_greybg[]      = "#073642";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { sol_base00, sol_greybg, sol_greybg },/*sol_base00, sol_base03, col_gray2*/
	[SchemeSel]  = { sol_cybri,  sol_base03, sol_cybri  },/*was sol_cybri, sol_base03, sol_base03*/
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance title         tags mask     isfloating   monitor */
	{ "Gimp",     NULL,    NULL,         0,            1,           -1 },
	{ NULL,       NULL,    "Buddy-List", 1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },/*useless*/
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", sol_base03, "-nf", sol_base00, "-sb", sol_base03, "-sf", sol_cybri, NULL };
static const char *termcmd[]     = { "urxvt", NULL };
static const char *termrgcmd[]   = { "urxvt", "-e", "ranger" };
static const char *firefoxcmd[]  = { "firefox-nightly", NULL };
static const char *chromcmd[]    = { "chromium", "-incognito", NULL };
static const char *pidgincmd[]   = { "pidgin", NULL };
static const char *nemocmd[]     = { "nemo", NULL };
static const char *poweroffcmd[] = { "poweroff", NULL };
static const char *rebootcmd[]   = { "reboot", NULL };
static const char *suspendcmd[]  = { "pm-suspend", NULL };
static const char *lockcmd[]     = { "slock", NULL };
static const char *appcmd[]      = { "xfce4-appfinder", NULL };
static const char *clipcmd[]     = { "clipmenu", NULL };
static const char *calendarcmd[] = { "orage", NULL };
static const char *wificmd[]     = { "urxvt", "-e", "sudo", "wifi-menu", NULL };
static const char *pavucmd[]     = { "pavucontrol", NULL };

static const char *upvol[]   = { "amixer", "set", "Master", "5%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "5%-",     NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };

/*static const char *upbri[]   = { "xbacklight", "+10",     NULL };
static const char *downbri[] = { "xbacklight", "-10",     NULL };*/
static const char *upbri[]   = { "bash", "/home/ffm/build/backlight/upbri.sh",     NULL };
static const char *downbri[] = { "bash", "/home/ffm/build/backlight/downbri.sh",   NULL };

static const char *screenshotcmd[] = { "gnome-screenshot", NULL };
static const char *screenshoticmd[] = { "gnome-screenshot", "-i", NULL };

static Key keys[] = {
	/* modifier                       key        function        argument */
	{ MODKEY,                         XK_p,      spawn,          {.v = dmenucmd   } },//Programme
	{ MODKEY|ShiftMask,               XK_Return, spawn,          {.v = termcmd    } },
	{ ControlMask|Mod1Mask,           XK_f,      spawn,          {.v = firefoxcmd } },
	{ ControlMask|Mod1Mask,           XK_c,      spawn,          {.v = chromcmd } },
	{ ControlMask|Mod1Mask,           XK_p,      spawn,          {.v = pidgincmd  } },
	{ ControlMask|Mod1Mask,           XK_t,      spawn,          {.v = termcmd    } },
	{ ControlMask|Mod1Mask,           XK_r,      spawn,          {.v = termrgcmd  } },
	{ ControlMask|Mod1Mask,           XK_e,      spawn,          {.v = nemocmd    } },
	{ ControlMask|Mod1Mask,           XK_l,      spawn,          {.v = lockcmd    } },
	{ ControlMask|Mod1Mask,           XK_a,      spawn,          {.v = appcmd     } },
	{ MODKEY,                         XK_e,      spawn,          {.v = nemocmd    } },
	{ Mod1Mask,                       XK_i,      spawn,          {.v = clipcmd    } },
	{ MODKEY,                         XK_F12,    spawn,          {.v = upvol      } },//Volume
    	{ MODKEY,                         XK_F11,    spawn,          {.v = downvol    } },
    	{ 0,                              0x1008ff13,spawn,          {.v = upvol      } },
    	{ 0,                              0x1008ff11,spawn,          {.v = downvol    } },
    	{ 0,                              XK_Print,  spawn,          {.v = screenshotcmd} },
    	{ ControlMask|Mod1Mask,           XK_s,      spawn,          {.v = screenshoticmd} },
    	{ MODKEY,                         XK_F10,    spawn,          {.v = mutevol    } },
    	{ 0,                              0x1008ff02,spawn,          {.v = upbri      } },//Brightness
    	{ 0,                              0x1008ff03,spawn,          {.v = downbri    } },
	{ ControlMask|Mod1Mask|ShiftMask, XK_o,      spawn,          {.v = poweroffcmd} },//Systemcommands
	{ ControlMask|Mod1Mask|ShiftMask, XK_r,      spawn,          {.v = rebootcmd  } },
	{ ShiftMask|Mod1Mask|ControlMask, XK_s,      spawn,          {.v = suspendcmd } },
	{ MODKEY,                         XK_b,      togglebar,      {0} },
	{ MODKEY,                         XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                         XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                         XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                         XK_l,      setmfact,       {.f = +0.05} },
 	{ MODKEY|ShiftMask,               0xf6,      setmfact,       {.f = 1.55} }, /*oe reset*/
	{ MODKEY,                         XK_Return, zoom,           {0} },
	{ MODKEY,                         XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,               XK_c,      killclient,     {0} },
	{ Mod1Mask,                       XK_F4,     killclient,     {0} },
	{ MODKEY,                         XK_t,      setlayout,      {.v = &layouts[0]} },/* tile */
	{ MODKEY,                         XK_f,      setlayout,      {.v = &layouts[1]} },/* floating */
	{ MODKEY,                         XK_m,      setlayout,      {.v = &layouts[2]} },/* monocle */
	{ MODKEY,                         XK_u,      setlayout,      {.v = &layouts[3]} },/* centeredmaster */
	{ MODKEY,                         XK_F13,    setlayout,      {.v = &layouts[4]} },/* centeredfloatingmaster (Disabled) */
	{ MODKEY,                         XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,               XK_space,  togglefloating, {0} },
	{ MODKEY,                         XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,               XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                         XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                         XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,               XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,               XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                          XK_1,                      0)
	TAGKEYS(                          XK_2,                      1)
	TAGKEYS(                          XK_3,                      2)
	TAGKEYS(                          XK_4,                      3)
	TAGKEYS(                          XK_5,                      4)
	TAGKEYS(                          XK_6,                      5)
	TAGKEYS(                          XK_7,                      6)
	TAGKEYS(                          XK_8,                      7)
	TAGKEYS(                          XK_9,                      8)
	{ MODKEY|ShiftMask,               XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
int Text1 = 96; // Date
int Text2 = 121; // Sound
int Text3 = 168; // Sys
// Text4 is everything left of Text3

static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText1,       0,              Button1,        spawn,          {.v = calendarcmd } },
	{ ClkStatusText2,       0,              Button1,        spawn,          {.v = pavucmd } },
	{ ClkStatusText2,       0,              Button4,        spawn,          {.v = upvol } },
	{ ClkStatusText2,       0,              Button5,        spawn,          {.v = downvol } },
	{ ClkStatusText3,       0,              Button1,        spawn,          {.v = termcmd } },
	{ ClkStatusText3,       0,              Button4,        spawn,          {.v = upbri } },
	{ ClkStatusText3,       0,              Button5,        spawn,          {.v = downbri } },
	{ ClkStatusText4,       0,              Button1,        spawn,          {.v = wificmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
