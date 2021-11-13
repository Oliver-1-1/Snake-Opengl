#include "Snake.h"

void Snake::update_vertices(glm::vec2 pos, float(&ver)[8])
{
    for (int i = 0; i < 8; i++)
    {
        if (!(i % 2)) ver[i] += pos.x;
        if (i % 2) ver[i] += pos.y;
    }
}

void Snake::update_check_if_collide(Node* n, float(&ver)[8])
{

    auto temp = n;
    n = n->next; // Do not count head pos
    glm::vec2 t = get_cords(ver);

	while (n->next != nullptr)
    {
        if (get_cords(n->data) == t)
            game_over = true;
		n = n->next;
    }

    n = temp;
}

void Snake::random_food(float(&ver)[8])
{
    float foods[8] = { 60.0f, 0.0f,80.0f, 0.0f,80.0f, 20.0f,60.0f, 20.0f };
    
    srand(time(NULL));
    int x = rand() % (800 / 20); // 0-40
    int y = rand() % (800 / 20); 

    for (int i = 0; i < 8; i++)
    {
        ver[i] = foods[i];
        if (!(i % 2)) ver[i] += x*20;
        if (i % 2)    ver[i] += y*20;
    }
}

void Snake::food_collide(Node* n, float(&food)[8])
{
    auto temp = n;
    n = n->next; // Do not count head pos
    glm::vec2 cord = get_cords(food);

    while (n->next != nullptr)
    {
        if (get_cords(n->data) == cord)
        {
            add_tail();
            random_food(food);
        }
        n = n->next;
    }

    n = temp;
}

glm::vec2 Snake::get_cords(float(&cord)[8])
{
    return glm::vec2(cord[0]/20, cord[1]/20);
}

void Snake::add_tail()
{
    
    auto t = head;
    while(head->next != NULL)
    {
        head = head->next;
    }
    if(head->next == NULL)
    {
        Node* new_node = new Node;
        *new_node->data = *head->data;
        update_vertices(glm::vec2(-20, 0), new_node->data);
        head->next = new_node;
    }
    head = t;
}



void Snake::move()
{
    if (direction== UP)
    {
        Node* new_node = new Node;
        *new_node = *head;
        update_vertices(glm::vec2(0, 20), new_node->data);
        Node::push(&head, new_node);
        Node::removeLastNode(head);

    }

    if (direction == RIGHT)
    {
        Node* new_node = new Node;
        *new_node = *head;
        update_vertices(glm::vec2(20, 0), new_node->data);
        Node::push(&head, new_node);
        Node::removeLastNode(head);
    }

    if (direction == DOWN)
    {
        Node* new_node = new Node;
        *new_node = *head;
        update_vertices(glm::vec2(0, -20), new_node->data);
        Node::push(&head, new_node);
        Node::removeLastNode(head);

    }

    if (direction == LEFT)
    {
        Node* new_node = new Node;
        *new_node = *head;
        update_vertices(glm::vec2(-20, 0), new_node->data);
        Node::push(&head, new_node);
        Node::removeLastNode(head);
       
    }
    direction = 0;
}

Node* Node::removeLastNode(Node* head)
{
    Node* n = head;
    while (n->next->next != nullptr)
        n = n->next;

    delete (n->next);

    n->next = nullptr;

    return head;
}

void Node::push(Node** head_ref, Node* n)
{
    n->next = (*head_ref);
    (*head_ref) = n;
}

Snake::Snake()
{
	head->next = second;
	second->next = third;
	third->next = fourth;
    fourth->next = nullptr;

	update_vertices(glm::vec2(0, -40), fourth->data);
    update_vertices(glm::vec2(0, 0), second->data);
    update_vertices(glm::vec2(0, -20), third->data);
    update_vertices(glm::vec2(0, 20), head->data);

    direction = 0;
    game_over = false;
}

