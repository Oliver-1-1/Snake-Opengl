#pragma once
#include <glm/glm.hpp>
#include <iostream>

enum Direction
{
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4
};

class Node
{
public:
    float data[8] = {0.0f, 0.0f,20.0f, 0.0f,20.0f, 20.0f,0.0f, 20.0f};
    Node* next;

    static void push(Node** head_ref, Node* n);
    static Node* removeLastNode(Node* head);

};

class Snake
{
public:
    Snake();
    Node* head = new Node;
    int direction;
    void move();
    static void update_vertices(glm::vec2 pos, float(&ver)[8]);
	void update_check_if_collide(Node* n, float(&ver)[8]);
    void random_food(float(&ver)[8]);
    void food_collide(Node* n, float(&food)[8]);
    static glm::vec2 get_cords(float(&cord)[8]);
    void add_tail();
    bool game_over;

private:
    Node* second = new Node;
    Node* third = new Node;
    Node* fourth = new Node;



};

