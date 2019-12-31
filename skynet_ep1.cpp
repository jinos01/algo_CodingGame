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
   int n, l, e, ei, si, n1, n2;         // n : 노드수  l : 간선 수  e : 출구 수
   cin >> n >> l >> e; cin.ignore();
   
   bool visited[501];
   int edge[501][501];

   //1. 엣지배열 생성
   for (int i = 0; i < 501;i++)
   {
      for (int j = 0; j < 501; j++)
      {
         edge[i][j] = 0;
      }
   }

   for (int i = 0; i < l; i++)
   {
      cin >> n1 >> n2;              // n1 , n2 : 노드 개수 
      edge[n1][n2] = 1;
      edge[n2][n1] = 1;
   }
   

   //출구배열
   bool exitNode[501];
   int exitNode_n[501];
   for (int i = 0;i < 501;i++) {
      exitNode[i] = false;
   }
   for (int i = 0; i < e; i++)
   {
      cin >> ei;                    // 출구 노드 
      exitNode[ei] = true;
      exitNode_n[i] = ei;  // exit 노드 저장 
   }
   
   int count[501];  // 노드에 연결된 출구 개수 카운트 
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
            count[i]++;  // 노드 i 에 연결된 출구의 갯수 
        }
      }       
   }
   
   
   queue<pos> q;

   while (1) {
      cin >> si;
      
      // visted 초기화
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
         //다음에 방문할 노드가 출구일 경우 
            
         
         if (exitNode[cur.nodeNumber]) {
            //그 노드 출력
            if(count[cur.prevNode] == 2)   // 노드에 연결된 출구가 2개이면 
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
         //다음에 방문할 노드가 출구가 아닐 경우
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