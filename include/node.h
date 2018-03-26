class Node
{
public:
    glm::mat4  transform;
    void(*render)(void);
    Node* sibling;
    Node* child;

    Node() :
        render(NULL), sibling(NULL), child(NULL) {}

    Node(glm::mat4& m, void(*render)(void), Node* sibling, Node* child) :
        transform(m), render(render), sibling(sibling), child(child) {}
};
