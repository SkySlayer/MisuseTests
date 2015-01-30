#include <iostream>
#include <ff.h>
#include <memory>
#include <algorithm>

class TreeNode;
typedef std::shared_ptr<TreeNode> TreeNode_ptr;

class TreeNode{
  public:
    TreeNode(int v): m_iValue(v){}
    
    int &  value() {return m_iValue;}
    const int & value() const{return m_iValue;}

    TreeNode_ptr & left() {return m_pLeft;}
    TreeNode_ptr & right(){return m_pRight;}

  protected:
    int m_iValue;
    TreeNode_ptr m_pLeft;
    TreeNode_ptr m_pRight;
};

TreeNode_ptr generate_tree(int nodes)
{
  std::vector<int> vs;
  for(int i = 0; i < nodes; i ++)
    vs.push_back(i);
  std::random_shuffle(vs.begin(), vs.end());

  TreeNode_ptr root(nullptr);

  for(size_t i = 0; i < vs.size(); i++)
  {
    TreeNode_ptr pn (new TreeNode(vs[i]));
    if(root == nullptr)
    {
      root = pn;
      continue;
    }
    else
    {
      if(root->value() > pn->value())
      {
        pn->left() = root;
        root = pn;
      }
      else{
        pn->right() = root;
        root = pn;
      }
    }
  }
  return root;
};

int get_depth(TreeNode_ptr n)
{
  if(n == nullptr)
    return 0;
  int ld = get_depth(n->left()) + 1;
  int rd = get_depth(n->right()) + 1;
  if(ld > rd)
    return ld;
  return rd;
}

int parallel_get_depth(TreeNode_ptr n)
{
  // write you code here, like get_depth();
}

int main(int argc, char *argv[])
{
  TreeNode_ptr p = generate_tree(1000);
  int d1 = get_depth(p);
  int d2 = parallel_get_depth(p);
  if(d1 == d2)
  {
    std::cout<<"Congrats! the output is totally correct!"<<std::endl;
  }
  else
  {
    std::cout<<"Sorry, wrong result! your answer is "<<d2<<", but the correct one should be "<<d1<<std::endl;
  }
  return 0;
}
