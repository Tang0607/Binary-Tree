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
    { // 析构函数释放子节点

        delete lChild;

        delete rChild;
    }
};


//红黑树的创建
class RBTree
{
public:
    int data;

    int color;//1代表黑，2代表红

    RBTree *lChild;

    RBTree *rChild;

    RBTree *father;

    RBTree(int val)
    { // 构造函数

        data = val;

        lChild = nullptr;

        rChild = nullptr;

        father = nullptr;
    }

    ~RBTree()
    {

        delete lChild;

        delete rChild;

    }
};

// 全局变量，表示红黑树的根节点
RBTree* root = nullptr;

const int BLACK = 1;

const int RED = 2;

// 左旋
void leftRotate(RBTree* x){

    RBTree* y = x->rChild;

    x->rChild = y->lChild;

    if (y->lChild != nullptr){

        y->lChild->father = x;
    }
    y->father = x->father;

    if (x->father == nullptr){

        root = y;

    } else if (x == x->father->lChild){

        x->father->lChild = y;

    } else {

        x->father->rChild = y;

    }
    y->lChild = x;

    x->father = y;
}

// 右旋
void rightRotate(RBTree* y){

    RBTree* x = y->lChild;

    y->lChild = x->rChild;

    if (x->rChild != nullptr){

        x->rChild->father = y;
    }
    x->father = y->father;

    if (y->father == nullptr){

        root = x;

    } else if (y == y->father->rChild){

        y->father->rChild = x;

    } else {

        y->father->lChild = x;
    }
    x->rChild = y;

    y->father = x;
}

void insertFixup(RBTree* z) {
    while (z->father != nullptr && z->father->color == RED) {

        if (z->father == z->father->father->lChild) {

            RBTree* y = z->father->father->rChild;

            if (y != nullptr && y->color == RED) {

                z->father->color = BLACK;

                y->color = BLACK;

                z->father->father->color = RED;

                z = z->father->father;

            } else {

                if (z == z->father->rChild) {

                    z = z->father;

                    leftRotate(z);

                }

                z->father->color = BLACK;

                z->father->father->color = RED;

                rightRotate(z->father->father);
            }
        } else {

            RBTree* y = z->father->father->lChild;

            if (y != nullptr && y->color == RED) {

                z->father->color = BLACK;

                y->color = BLACK;

                z->father->father->color = RED;

                z = z->father->father;

            } else {

                if (z == z->father->lChild) {

                    z = z->father;

                    rightRotate(z);

                }
                z->father->color = BLACK;

                z->father->father->color = RED;

                leftRotate(z->father->father);
            }
        }
    }
    root->color = BLACK;
}

RBTree* insert(int val) {

    RBTree* z = new RBTree(val);

    z->color = RED;

    RBTree* y = nullptr;

    RBTree* x = root;

    while (x != nullptr) {

        y = x;

        if (z->data < x->data) {

            x = x->lChild;

        } else {

            x = x->rChild;
        }
    }

    z->father = y;

    if (y == nullptr) {

        root = z;

    } else if (z->data < y->data) {

        y->lChild = z;

    } else {

        y->rChild = z;
    }

    insertFixup(z);

    return z;
}


// 先序创建二叉树
void CreateBiTree(BiTNode *&T)
{

    int ch;

    cout << "输入节点数据（-1表示空节点）：";

    cin >> ch;

    if (ch == -1)
    {

        T = nullptr;

        return;
    } // 结果为空则直接返回

    T = new BiTNode(ch);

    cout << "创建 " << T->data << " 的左子节点：" << endl; // 创建左子节点

    CreateBiTree(T->lChild);

    cout << "创建 " << T->data << " 的右子节点：" << endl; // 创建右子节点

    CreateBiTree(T->rChild);
}

// 创建深度为h的二叉树
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
BiTNode *insert(BiTNode *T, int val)
{
    if (T == nullptr) // 若节点为空，那么将数据传至此节点并创建此节点下的左右子节点
    {
        BiTNode *newNode = new BiTNode(val);

        newNode->data = val;

        newNode->lChild = nullptr;

        newNode->rChild = nullptr;

        return newNode;
    }
    if (val < T->data) // 若节点不为空，那么比较节点数据得出去往左右子树
    {
        T->lChild = insert(T->lChild, val);
    }
    else if (val > T->data)
    {
        T->rChild = insert(T->rChild, val);
    }
    return T;
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
        {
            q.push(T->lChild);
        }

        if (T->rChild)
        {
            q.push(T->rChild);
        }
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

        if (T->rChild != nullptr)
        { // 由于栈是先进后出，因此先使右节点入栈

            nodeStack.push(T->rChild);
        }

        if (T->lChild != nullptr)
        {

            nodeStack.push(T->lChild);
        }
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

    BiTNode *visitedNode = T;

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

            currentNode = nullptr; // 防止重复访问左子树

            nodeStack.pop(); // 出栈
        }
    }
}

// ========== 打印函数 ==========
void PrintTreeRotatedLeft(BiTNode *node, int space = 0, bool isLeft = false)
{
    const int SPACING = 4; // 控制节点间距

    if (node == nullptr)
    {
        return;
    }

    // 先打印右子树（在打印区域的右侧）
    PrintTreeRotatedLeft(node->rChild, space + SPACING, false);

    // 打印当前节点前的连接线
    if (space > 0)
    {
        cout << string(space, ' ');

        if (isLeft)
        {
            cout << "└──"; // 左子节点连接线
        }
        else
        {
            cout << "┌──"; // 右子节点连接线
        }
    }

    // 打印当前节点
    cout << node->data << "\n";

    // 打印左子树（在打印区域的左侧）
    PrintTreeRotatedLeft(node->lChild, space + SPACING, true);
}

// 普通二叉树的查找（使用深度优先搜索）
BiTNode *searchBinaryTree(BiTNode *T, int target)
{
    if (T == nullptr || T->data == target) ////与本节点的数据比较
    {
        return T;
    }

    // 先在左子树中查找
    BiTNode *lChild = searchBinaryTree(T->lChild, target);

    if (lChild != nullptr)
    {
        return lChild;
    }
    // 再在右子树中查找
    return searchBinaryTree(T->rChild, target);
}

BiTNode *searchSeBinaryTree(BiTNode *T, int target)
// 二叉搜索树（有序二叉树）的查找
{
    if (T == nullptr || T->data == target) // 与本节点的数据比较
    {
        return T;
    }
    if (target < T->data) // 若小于则向左传递
    {
        return searchSeBinaryTree(T->lChild, target);
    }
    else
    {
        return searchSeBinaryTree(T->rChild, target); // 大于向右传递
    }
}

int main()
{

    /*BiTNode *T = nullptr;

    int i, a, b = 0;

    int c = 0;

    int target;

    cout << "=== 开始生成二叉树 ===" << endl;

    cout << "接下来您可以选择生成自定义二叉树或生成自定义数据的有序二叉树或深度为h的满二叉树（拥有255个节点的满二叉树深度h=8（2^8-1=255)）" << endl;

    cout << "输入1生成自定义数据的有序二叉树，输入2生成自定义二叉树，输入3生成深度为h的满二叉树" << endl;

    cin >> b;

    if (b == 2)
    {
        CreateBiTree(T);
    }
    else if (b == 1)
    {
        while (c != -1)
        {
            cout << "请输入节点数据(-1表示结束插入)：" << endl;

            cin >> c;

            if (c != -1)
            {
                T = insert(T, c);
            }
        }
    }
    else if (b == 3)
    {
        cout << "请输入h的具体数值：" << endl;

        cin >> i;

        CreateFullBiTree(T, i);
    }

    cout << "=== 接下来实现二叉树的遍历 ===" << endl;

    cout << "您可以选择用递归或堆栈的方法进行遍历(包括前序、中序、后序的遍历）" << endl;

    cout << "输入1使用递归方法进行遍历，输入2使用堆栈方法进行遍历" << endl;

    cin >> a;

    if (a == 1)
    {

        cout << "\n=== 遍历结果 ===" << endl;

        cout << "先序遍历：";

        PreOrderBiTree(T);

        cout << "\n中序遍历：";

        MiddleOrderBiTree(T);

        cout << "\n后序遍历：";

        PostOrderBiTree(T);
    }

    else if (a == 2)
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

    cout << endl;

    cout << "\n\n===打印二叉树=== " << endl;

    PrintTreeRotatedLeft(T);

    cout << "\n\n===查找二叉树=== " << endl;

    cout << "请输入要查找的数据：" << endl;

    cin >> target;

    if (b == 1)
    {
        BiTNode *result = searchSeBinaryTree(T, target);

        if (result)
        {
            cout << "在二叉树中找到了节点: " << result->data << endl;
        }
        else
        {
            cout << "在二叉树中未找到目标节点" << endl;
        }
    }
    else
    {
        BiTNode *result = searchBinaryTree(T, target);

        if (result)
        {
            cout << "在二叉树中找到了节点: " << result->data << endl;
        }
        else
        {
            cout << "在二叉树中未找到目标节点" << endl;
        }
    }

    delete T;*/ // 动态分配后释放内存

    int i;

    cout<<"接下来创建红黑树"<<endl;

    cout<<"请输入节点的数据，程序将自动插入到合适的位置并调整红黑树结构"<<endl;

    while(i!=-1)
    {
        cin>>i;

        insert(i);
    }

    //输出遍历红黑树

    return 0;
}
