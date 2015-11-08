#include "SunGame.h"
#include "./SunButtonState.h"
#include "./SunScene.h"

GLfloat screenWidth = 800;
GLfloat screenHeight = 600;

#ifdef RETINA
screenWidth = 1600;
screenHeight = 1200;
#endif

GLfloat lastX = 400;
GLfloat lastY = 300;
bool firstMouseTime = true;

// Maps containing GLFW button ids and their respective states
// NOTE: CLEAN UP OLDBUTTONS

map<int, SunButtonState> buttons;
map<int, SunButtonState> oldButtons;

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;

GLfloat xOffset;
GLfloat yOffset;

GLfloat lastXOffset;
GLfloat lastYOffset;

// Called when a key is pressed

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // If it had a transition, change its state
    
    if (action == GLFW_PRESS && buttons[key] != SunButtonStatePressedEdge) {
        buttons[key] = SunButtonStatePressedEdge;
    } else if (action == GLFW_RELEASE)
        buttons[key] = SunButtonStateReleased;
}

// Calculate the mouse position when it changes

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouseTime) {
        lastX = xpos;
        lastY = ypos;
        firstMouseTime = false;
    }
    
    xOffset = xpos - lastX;
    yOffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    GLfloat sensitivity = 0.15;
    xOffset *= sensitivity;
    yOffset *= sensitivity;
}

// Called when a mouse button is pressed

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    // If it had a transition, change its state
    
    if (action == GLFW_PRESS)
        buttons[button] = SunButtonStatePressedEdge;
    else if (action == GLFW_RELEASE)
        buttons[button] = SunButtonStateReleased;
}



void SunGame::loop() {
    while (!glfwWindowShouldClose(window)) {
        // Calculate the frame time (NEEDS CLEAN UP)

        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Set old buttons (NEEDS CLEAN UP)

        oldButtons = buttons;

        // Poll GLFW events to check for any input

        glfwPollEvents();

        // Set any button that is pressed for the second cycle on to a different state (NEEDS CLEAN UP)

        for (auto iterator = buttons.begin(); iterator != buttons.end(); ++iterator) {
            int currentButton = iterator->first;

            SunButtonState currentValue = buttons[currentButton];
            SunButtonState oldValue = oldButtons[currentButton];

            if (currentValue == SunButtonStatePressedEdge && oldValue == SunButtonStatePressedEdge) {
                buttons[currentButton] = SunButtonStatePressed;
            }
        }

        if (scene->getDoCameraInput() == true) {
            // Tell the camera to do movement (NEEDS CLEAN UP)

            if (lastXOffset != xOffset && lastYOffset != yOffset)
                scene->getCamera().doCameraMovement(buttons, deltaTime, xOffset, yOffset);
            if (lastXOffset == xOffset && lastYOffset != yOffset)
                scene->getCamera().doCameraMovement(buttons, deltaTime, 0, yOffset);
            if (lastXOffset != xOffset && lastYOffset != yOffset)
                scene->getCamera().doCameraMovement(buttons, deltaTime, xOffset, 0);
            else
                scene->getCamera().doCameraMovement(buttons, deltaTime, 0, 0);

            lastXOffset = xOffset;
            lastYOffset = yOffset;
        } else {
            xOffset = lastXOffset;
            yOffset = lastYOffset;
        }

        scene->getListener().setPosition(scene->getCamera().getPosition());
        scene->getListener().setDirection(scene->getCamera().getDirection());

        // Tell the renderer to do its cycle

        scene->cycle(buttons, deltaTime);
    }
    glfwTerminate();
}

void SunGame::cleanUp() {
	glfwTerminate();
}

void SunGame::initialize(bool _useMSAA, GLint _MSAASampleCount) {
    // Initialize GLFW and give window hints

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    if (_useMSAA == true)
        glfwWindowHint(GLFW_SAMPLES, _MSAASampleCount);

    window = glfwCreateWindow(screenWidth, screenHeight, "Sunglasses", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }

    // Set the viewport size (NEEDS CLEAN UP)
    glViewport(0, 0, screenWidth, screenHeight);

    // Set the input callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Set the mouse input mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable multisampling
    if (_useMSAA == true) {
        glEnable(GL_MULTISAMPLE);
        glfwWindowHint(GLFW_SAMPLES, _MSAASampleCount);
    }

    // Enable hardware gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Set blending function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the clear color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    scene = new SunScene("./SceneDemo.xml", window);
}
