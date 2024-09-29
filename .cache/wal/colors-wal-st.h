const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#061617", /* black   */
  [1] = "#5C6867", /* red     */
  [2] = "#7C8470", /* green   */
  [3] = "#757D83", /* yellow  */
  [4] = "#7B8389", /* blue    */
  [5] = "#8B9097", /* magenta */
  [6] = "#9A9FA5", /* cyan    */
  [7] = "#caccd0", /* white   */

  /* 8 bright colors */
  [8]  = "#8d8e91",  /* black   */
  [9]  = "#5C6867",  /* red     */
  [10] = "#7C8470", /* green   */
  [11] = "#757D83", /* yellow  */
  [12] = "#7B8389", /* blue    */
  [13] = "#8B9097", /* magenta */
  [14] = "#9A9FA5", /* cyan    */
  [15] = "#caccd0", /* white   */

  /* special colors */
  [256] = "#061617", /* background */
  [257] = "#caccd0", /* foreground */
  [258] = "#caccd0",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
