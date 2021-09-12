/* sticky press
if rex_space_press_since_release_times > KEY_HOLD_THRESHOLD, pressing key behavior will be judged as REX_KEY_HOLD
else REX_KEY_PRESS
*/
#define KEY_HOLD_THRESHOLD 3

/* calculate ratio to center the widget */
void nk_layout_calc_center_array(float window_total, float item_total, float layout_array[3]);
