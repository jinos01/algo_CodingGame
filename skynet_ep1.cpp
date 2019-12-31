#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

typedef struct pos {
   int nodeNumber;
   int prevNode;
}pos;

using namespace std;

int main() {
   int n, l, e, ei, si, n1, n2;         // n : ����  l : ���� ��  e : �ⱸ ��
   cin >> n >> l >> e; cin.ignore();
   
   bool visited[501];
   int edge[501][501];

   //1. �����迭 ����
   for (int i = 0; i < 501;i++)
   {
      for (int j = 0; j < 501; j++)
      {
         edge[i][j] = 0;
      }
   }

   for (int i = 0; i < l; i++)
   {
      cin >> n1 >> n2;              // n1 , n2 : ��� ���� 
      edge[n1][n2] = 1;
      edge[n2][n1] = 1;
   }
   

   //�ⱸ�迭
   bool exitNode[501];
   int exitNode_n[501];
   for (int i = 0;i < 501;i++) {
      exitNode[i] = false;
   }
   for (int i = 0; i < e; i++)
   {
      cin >> ei;                    // �ⱸ ��� 
      exitNode[ei] = true;
      exitNode_n[i] = ei;  // exit ��� ���� 
   }
   
   int count[501];  // ��忡 ����� �ⱸ ���� ī��Ʈ 
   for (int i = 0;i < 501;i++) {
      count[i] = 0;
   }
   
   for(int i = 0 ; i < l; i++)        //
   {
      
      for(int k = 0 ; k < e ; k++)
      {
        int num = exitNode_n[k];
        if(edge[i][num] == 1 && edge[num][i] == 1)
        {
            count[i]++;  // ��� i �� ����� �ⱸ�� ���� 
        }
      }       
   }
   
   
   queue<pos> q;

   while (1) {
      cin >> si;
      
      // visted �ʱ�ȭ
      for (int i = 0; i < 501; i++)
      {
         visited[i] = false;
      }

      pos temp;
      temp.nodeNumber = si;
      temp.prevNode = si;
      q.push(temp);
      visited[si] = true;
      while (!q.empty())
      {
         pos cur = q.front();
         q.pop();
         //������ �湮�� ��尡 �ⱸ�� ��� 
            
         
         if (exitNode[cur.nodeNumber]) {
            //�� ��� ���
            if(count[cur.prevNode] == 2)   // ��忡 ����� �ⱸ�� 2���̸� 
            {
                cout << cur.prevNode << " " << cur.nodeNumber << endl;
                count[cur.prevNode]--;
                
                break;
            }
            else if (count[cur.prevNode] == 1)
            {
                cout << cur.prevNode << " " << cur.nodeNumber << endl;
                count[cur.prevNode]--;
                while(!q.empty())
                {
                    q.pop();
                }
                break;    
            }
            else
            {
                cout << cur.prevNode << " " << cur.nodeNumber << endl;
                while(!q.empty())
                {
                    q.pop();
                }
                break;
            }
         }  
         //������ �湮�� ��尡 �ⱸ�� �ƴ� ���
         else 
         {
            
            for (int i = 0; i < 501;i++)
            {     
               if ((edge[cur.nodeNumber][i] == 1) && (!visited[i]))
               {
                  pos temp;
                  temp.nodeNumber = i;
                  temp.prevNode = cur.nodeNumber;
                  q.push(temp);
                  visited[i] = true;
               }
            }
         }
      }
   }
}