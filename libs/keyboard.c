enum rex_key_code
{
    REX_KEY_CODE_DOWN = 1, /* down key */
    REX_KEY_CODE_SPACE,    /* space key */
};

enum rex_key_status
{
    REX_KEY_STATUS_RELEASE, /* not press */
    REX_KEY_STATUS_PRESS,   /* press then release */
    REX_KEY_STATUS_REPEAT,  /* long press */
};

struct rex_game_key
{
    enum rex_key_code code;     /* valid key code */
    enum rex_key_status status; /* key status */
};

struct rex_game_key rex_input_key; /* valid key input from keyboard */

void rex_keyboard_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_SPACE:
        rex_input_key.code = REX_KEY_CODE_SPACE;
        switch (action)
        {
        case GLFW_RELEASE:
            rex_input_key.status = REX_KEY_STATUS_RELEASE;
            break;
        case GLFW_PRESS:
            rex_input_key.status = REX_KEY_STATUS_PRESS;
            break;
        case GLFW_REPEAT:
            rex_input_key.status = REX_KEY_STATUS_REPEAT;
            break;
        }
        break;
    case GLFW_KEY_DOWN:
        rex_input_key.code = REX_KEY_CODE_DOWN;
        switch (action)
        {
        case GLFW_RELEASE:
            rex_input_key.status = REX_KEY_STATUS_RELEASE;
            break;
        case GLFW_PRESS:
            rex_input_key.status = REX_KEY_STATUS_PRESS;
            break;
        case GLFW_REPEAT:
            rex_input_key.status = REX_KEY_STATUS_REPEAT;
            break;
        }
        break;
    }
}

void rex_keyboard_register_keyboard_events(void)
{
    glfwSetKeyCallback(glfw.win, rex_keyboard_key_callback);
}
