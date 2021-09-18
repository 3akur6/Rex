enum rex_key_code
{
    REX_KEY_DOWN,  /* down key */
    REX_KEY_SPACE, /* space key */
};

enum rex_key_status
{
    REX_KEY_PRESS,      /* press then release */
    REX_KEY_LONG_PRESS, /* long press */
    REX_KEY_RELEASE,    /* not press */
    REX_KEY_HOLD        /* keep pressing key for some time */
};

struct rex_game_key
{
    enum rex_key_code code;     /* valid key code */
    enum rex_key_status status; /* key status */
};

struct rex_game_key rex_input_key; /* valid key input from keyboard */

static unsigned int rex_space_press_since_release_times = 0; /* reset when space is released */

enum rex_key_status rex_get_space_status(void)
{ /* only check status when space is released */
    /* check raw space press status */
    unsigned int rex_space_press_since_release_times_saved = rex_space_press_since_release_times;

    if (glfwGetKey(glfw.win, GLFW_KEY_SPACE) == GLFW_PRESS)
        rex_space_press_since_release_times++;
    else
        rex_space_press_since_release_times = 0;

    /* space released */
    if (rex_space_press_since_release_times_saved == 0)
        return REX_KEY_RELEASE;

    /* still press */
    else if (rex_space_press_since_release_times >= KEY_HOLD_THRESHOLD)
        return REX_KEY_HOLD;

    /* space pressed */
    else if (rex_space_press_since_release_times_saved >= KEY_HOLD_THRESHOLD && rex_space_press_since_release_times == 0)
        return REX_KEY_LONG_PRESS;

    /* space hold */
    else /* if (rex_space_press_since_release_times > KEY_HOLD_THRESHOLD) */
        return REX_KEY_PRESS;
}

void rex_keyboard_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
    }
    switch (key)
    {
    case GLFW_KEY_SPACE:
        switch (action)
        {
        case GLFW_RELEASE:
            break;
        case GLFW_PRESS:
            break;
        case GLFW_REPEAT:
            break;
        }
        break;
    case GLFW_KEY_DOWN:
        switch (action)
        {
        case GLFW_RELEASE:
            break;
        case GLFW_PRESS:
            break;
        case GLFW_REPEAT:
            break;
        }
        break;
    }
}

void rex_keyboard_register_keyboard_event(void)
{
    glfwSetKeyCallback(glfw.win, rex_keyboard_key_callback);
}
