#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "Window.h"
#include "Shader.h"
#include "Debug.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Snake.h"

Snake snake;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void send_data_to_buffer(float(&ver)[8]);
void draw(int shader_program_id);
float food[8] = { 60.0f, 0.0f,80.0f, 0.0f,80.0f, 20.0f,60.0f, 20.0f };

unsigned int VBO, VAO, ibo;

int indices[] = { 0, 1, 2, 2, 3, 0 };

int main(void)
{
	const Window window(800,800, "Zepta");
    Shader shader("vertex.glsl", "fragment.glsl");

    glfwSetKeyCallback(window.window, key_callback);

    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glGenBuffers(1, &VBO));
    GLCall(glBindVertexArray(VAO));

    send_data_to_buffer(snake.head->data);

    //send to location 0 in shader
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));

    //Bind indices to reuse vertices
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	const glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);

    // Use shader before sending uniforms to shader
    glUseProgram(shader.program);
    shader.set_mat4("MVP", proj);
    shader.set_vec4("color", glm::vec4(0.0f, 0.0f, 1.0f, 1.f)); // BLUE
    
    while (!glfwWindowShouldClose(window.window) && !snake.game_over)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        snake.update_check_if_collide(snake.head, snake.head->data); // Check collsion and end game if that is the case
        snake.food_collide(snake.head, food);
        snake.move(); // Move linked list
        draw(shader.program); // Draw by iterating through liked list


        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (action)
    {
    case GLFW_PRESS:
        switch (key)
        {
			case GLFW_KEY_W : snake.direction =  UP;    break;
			case GLFW_KEY_S:  snake.direction  = DOWN;  break;
			case GLFW_KEY_A:  snake.direction  = LEFT;  break;
			case GLFW_KEY_D:  snake.direction  = RIGHT; break;
			case GLFW_KEY_G:  snake.add_tail();         break;
			default:;
        }
    default:;
    }
}

void send_data_to_buffer(float(&ver)[8])
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW));
}

void draw(int shader_program_id)
{
	const auto temp = snake.head;
    GLCall(int location = glGetUniformLocation(shader_program_id, "color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.0f, 0.0f, 1.0f, 1.f));
    while (snake.head != NULL)
    {
        send_data_to_buffer(snake.head->data);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
        snake.head = snake.head->next;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    }

    // Draw food
    send_data_to_buffer(food);
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.f));
	//shader.set_vec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.f)); // RED

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));

    snake.head = temp;
}
