static const char norm_fg[] = "#cfdbd9";
static const char norm_bg[] = "#121f24";
static const char norm_border[] = "#909997";

static const char sel_fg[] = "#cfdbd9";
static const char sel_bg[] = "#A0997F";
static const char sel_border[] = "#cfdbd9";

static const char urg_fg[] = "#cfdbd9";
static const char urg_bg[] = "#89917A";
static const char urg_border[] = "#89917A";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
