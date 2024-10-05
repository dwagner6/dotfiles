const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#121f24", /* black   */
  [1] = "#89917A", /* red     */
  [2] = "#A0997F", /* green   */
  [3] = "#5C7788", /* yellow  */
  [4] = "#6E998B", /* blue    */
  [5] = "#8D9886", /* magenta */
  [6] = "#9CA698", /* cyan    */
  [7] = "#cfdbd9", /* white   */

  /* 8 bright colors */
  [8]  = "#909997",  /* black   */
  [9]  = "#89917A",  /* red     */
  [10] = "#A0997F", /* green   */
  [11] = "#5C7788", /* yellow  */
  [12] = "#6E998B", /* blue    */
  [13] = "#8D9886", /* magenta */
  [14] = "#9CA698", /* cyan    */
  [15] = "#cfdbd9", /* white   */

  /* special colors */
  [256] = "#121f24", /* background */
  [257] = "#cfdbd9", /* foreground */
  [258] = "#cfdbd9",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
