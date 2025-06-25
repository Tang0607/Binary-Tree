#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// 二叉树的节点类
class BiTNode
{
public:
    int data; // 节点数据

    BiTNode *lChild; // 左子节点指针

    BiTNode *rChild; // 右子节点指针

    BiTNode(int val)
    { // 构造函数

        data = val; // 给节点赋值

        lChild = nullptr; // 左子节点赋值

        rChild = nullptr; // 右子节点赋值
    }

    ~BiTNode()
    { // 析构函数释放子节点(不是动态分配内存为什么需要delete）

        delete lChild;

        delete rChild;
    }
};

// 先序创建二叉树
/*void CreateBiTree(BiTNode*& T) {

    int ch;

    cout << "输入节点值（-1表示空节点）：";

    cin >> ch;

    if (ch == -1) {

        T = nullptr;

        return;
    }                   //结果为空则直接返回

    T = new BiTNode(ch);

    cout << "创建 " << T->data << " 的左子节点：" << endl;    //创建左子节点

    CreateBiTree(T->lChild);

    cout << "创建 " << T->data << " 的右子节点：" << endl;    //创建右子节点

    CreateBiTree(T->rChild);
}*/

// 创建有255个节点的二叉树
void CreateFullBiTree(BiTNode *&T, int depth)
{

    if (depth <= 0)
    {

        T = nullptr;

        return;
    }

    // 先创建根节点（数据可设为层序编号或自定义）
    static int nodeVal = 1; // 节点值从1开始编号

    T = new BiTNode(nodeVal++);

    // 递归创建左右子树
    CreateFullBiTree(T->lChild, depth - 1);

    CreateFullBiTree(T->rChild, depth - 1);
}

// 创建有序二叉树
void CreatSequentialBiTree(BiTNode *&T)
{

    int i, d;

    cout << "请输入节点的数据:" << endl;

    cin >> i;

    cout << "请继续输入插入的数据（输入-1则结束创建）：" << endl;

    cin >> d;

    if (d = -1)
    {

        T = nullptr;

        return;
    }

    if (d > i)
    {

        // CreatSequentialBiTree(T->rChild);
    }

    if (d < i)
    {

        // CreatSequentialBiTree(T->lChild);
    }
}

// 先序遍历（递归）
void PreOrderBiTree(BiTNode *T)
{

    if (T == nullptr)
    {

        return;
    }

    cout << T->data << " ";

    PreOrderBiTree(T->lChild);

    PreOrderBiTree(T->rChild);
}

// 中序遍历（递归）
void MiddleOrderBiTree(BiTNode *T)
{

    if (T == nullptr)
    {

        return;
    }

    MiddleOrderBiTree(T->lChild);

    cout << T->data << " ";

    MiddleOrderBiTree(T->rChild);
}

// 后序遍历（递归）
void PostOrderBiTree(BiTNode *T)
{

    if (T == nullptr)
    {

        return;
    }

    PostOrderBiTree(T->lChild);

    PostOrderBiTree(T->rChild);

    cout << T->data << " ";
}

// 层序遍历
void levelOrder(BiTNode *T)
{

    if (T == nullptr)
    {

        return;
    }

    queue<BiTNode *> q;

    q.push(T);

    while (!q.empty())
    {

        BiTNode *T = q.front();

        q.pop();

        cout << T->data << " ";

        if (T->lChild)
            q.push(T->lChild);

        if (T->rChild)
            q.push(T->rChild);
    }
}

// 先序遍历（堆栈）
void PreOrderBiTree2(BiTNode *T)
{

    if (T == nullptr)
    { // 空树直接返回

        return;
    }

    stack<BiTNode *> nodeStack; // 创建栈

    nodeStack.push(T); // 根节点入栈

    while (!nodeStack.empty())
    {

        BiTNode *T = nodeStack.top(); // 取栈的顶节点

        nodeStack.pop(); // 顶节点出栈

        cout << T->data << " ";
    }

    if (T->rChild != nullptr)
    { // 由于栈是先进后出，因此先使右节点入栈

        nodeStack.push(T->rChild);
    }

    if (T->lChild != nullptr)
    {

        nodeStack.push(T->lChild);
    }
}

// 中序遍历（堆栈）
void MiddleOrderBiTree2(BiTNode *T)
{

    stack<BiTNode *> nodestack;

    BiTNode *cur = T; // 当前遍历到的节点

    while (cur != nullptr || !nodestack.empty())
    { // 把当前节点的所有左子节点压栈

        while (cur != nullptr)
        {

            nodestack.push(cur);

            cur = cur->lChild;
        }

        cur = nodestack.top(); // 弹出栈顶访问数据

        nodestack.pop();

        cout << cur->data << " ";

        cur = cur->rChild; // 处理右子树
    }
}

// 后序遍历（堆栈）
void PostOrderBiTree2(BiTNode *T)
{

    if (T == nullptr)
    { // 空树则直接结束

        return;
    }

    stack<BiTNode *> nodeStack; // 创建一个栈保存节点

    BiTNode *currentNode = T; // 维护一个当前节点指针

    BiTNode *visitedNode = T; // 保存上次访问的节点，初始化为root是利用二叉树是无环图

    while (currentNode || !nodeStack.empty())
    {

        // 当前节点非空，沿着左子树方向入栈
        while (currentNode)
        {

            nodeStack.push(currentNode);

            currentNode = currentNode->lChild;
        }
        currentNode = nodeStack.top(); // 取栈顶元素

        // 如果栈顶元素有右子树，且未被访问
        if (currentNode->rChild && currentNode->rChild != visitedNode)
        {

            currentNode = currentNode->rChild;
        }
        else
        {

            printf("%d ", currentNode->data); // 访问节点数据

            visitedNode = currentNode; // 记录当前访问的节点

            currentNode = nullptr; // 当前节点置为NULL，防止重复访问左子树

            nodeStack.pop(); // 出栈
        }
    }
}

// 计算树的深度
/*int TreeDeep(BiTNode* T) {
    if (T == nullptr){

        return 0;

    }

    int leftDeep = TreeDeep(T->lChild);

    int rightDeep = TreeDeep(T->rChild);

    return (leftDeep > rightDeep ? leftDeep : rightDeep) + 1;
}*/

int main()
{

    BiTNode *T = nullptr;

    cout << "=== 开始生成二叉树 ===" << endl;

    cout << "接下来创建深度为h的满二叉树,请输入h的具体数值：" << endl;

    cout << "注：拥有255个节点的满二叉树深度h=8（2^8-1=255)" << endl;

    int i, a;

    cin >> i;

    CreateFullBiTree(T, i);

    cout << "您可以选择用递归或堆栈的方法进行遍历(包括前序、中序、后序的遍历）" << endl;

    cout << "输入1使用递归方法进行遍历，输入2使用堆栈方法进行遍历" << endl;

    cin >> a;

    /*cout << "=== 开始创建二叉树 ===" << endl;

    CreateBiTree(T);*/

    if (a = 1)
    {

        cout << "\n=== 遍历结果 ===" << endl;

        cout << "先序遍历：";

        PreOrderBiTree(T);

        cout << "\n中序遍历：";

        MiddleOrderBiTree(T);

        cout << "\n后序遍历：";

        PostOrderBiTree(T);
    }

    if (a = 2)
    {

        cout << "\n=== 遍历结果 ===" << endl;

        cout << "先序遍历：";

        PreOrderBiTree2(T);

        cout << "\n中序遍历：";

        MiddleOrderBiTree2(T);

        cout << "\n后序遍历：";

        PostOrderBiTree2(T);
    }

    cout << "\n层序遍历：";

    levelOrder(T);

    // cout << "\n\n=== 树的属性 ===" << endl;

    // cout << "树的深度：" << TreeDeep(T) << endl;

    delete T; // 动态分配后释放内存

    return 0;
}