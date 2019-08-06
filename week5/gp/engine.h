struct Action
{
    int toGo;
    string description;
};


class You
{
public:
    int m_currentScene;
    Action m_choices[3];
    You(){m_currentScene = 1;};  //default
    int display(string file);  //looks at m_currentScene, dispays scenario, choices, and sets up m_choices
    void choose(int n);    //chooses, n stand for max choices
    bool tick(string file);
};

