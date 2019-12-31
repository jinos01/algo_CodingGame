#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void init();
int n, l, e, ei, si, n1, n2;

//방문여부와 출발노드에서 도착노드까지의 거리 정보를 저장하기 위한 pi이름의 구조체
typedef struct pi
{
   bool det_bool;
   int distance_;
};
//pi형식을 담는 배열 
pi visited[501];

//간선정보 배열
int edge[501][501];

//자신과 부모노드의 정보를 저장한 pos이름의 구조체
typedef struct pos {
   int node;
   int pre_node;
}pos;

//노드가 몇개의 출구와 연결되어있는지를 저장하는 배열
int real_node[501];

//출구노드 배열
bool exitNode[501];

//pos형식의 queue 생성
queue<pos> q;

//shortest_path함수를 수행할 때 도착노드의 부모노드 정보를 저장하는 temp_out, 최종 출력 노드 정보를 담는 output_
int temp_out, output_;

//노드와 노드 사이의 최단거리 출력함수 >> bfs사용
int shortest_path(int start_point, int end_point);

int main()
{
   init();

   while (1) {
      cin >> si;
      int min = 1000;
      int exit_info = 0;
      for (int i = 0; i < 501; i++)
      {
         if (exitNode[i] == true)
         {
            //출구노드와 입력한 si값사이의 최단경로를 구한다.
            int shortest1 = shortest_path(si, i);

            //최단경로의 최솟값을 구하여 그 때의 출구노드와 그 출구노드의 부모노드를 저장한다.
            if ((shortest1 < min) && (shortest1 > 0))
            {
               min = shortest1;
               exit_info = i;
               output_ = temp_out;
            }
         }
      }

      //최단경로의 최솟값이 1이라는 것은 바로 다음에 방문할 노드가 출구라는 뜻이므로 출구노드와 그 출구노드의 부모노드에 해당하는 간선정보를 삭제한다.
      if (min == 1)
      {
         //노드와 출구의 모든 간선정보 삭제
         edge[si][exit_info] = 0;
         edge[exit_info][si] = 0;
         real_node[si]--;
         cout << si << " " << exit_info << endl;
      }

      //최단경로의 최솟값이 1이 아니라는 것은 아직 급하지 않으므로 미리 다른 간선정보를 삭제한다.
      else
      {
         int min = 1000;
         for (int i = 0; i < 501; i++)
         {
            if (exitNode[i] == true)
            {   
               //출구노드 2개와 연결되어있는 노드의 간선을 우선적으로 제거하기 위해 최단경로를 다시 구한다.
               int shortest2 = shortest_path(si, i);
               if ((shortest2 < min) && (real_node[temp_out] == 2) && (shortest2 > 0))
               {
                  min = shortest2;
                  exit_info = i;
                  output_ = temp_out;
               }
            }
         }

         //그 간선에 해당하는 모든 정보 삭제
         edge[exit_info][output_] = 0;
         edge[output_][exit_info] = 0;
         real_node[output_]--;
         cout << exit_info << " " << output_ << endl;
      }
   }

}

//대부분의 입력정보를 받는 함수
void init()
{
   cin >> n >> l >> e; cin.ignore();
   //간선배열 초기화
   for (int i = 0; i < 501;i++)
   {
      for (int j = 0; j < 501; j++)
      {
         edge[i][j] = 0;
      }
   }

   //간선정보 갱신
   for (int i = 0; i < l; i++)
   {
      cin >> n1 >> n2;
      edge[n1][n2] = 1;
      edge[n2][n1] = 1;
   }

   //출구노드를 저장하는 배열과 노드가 몇개의 출구와 연결되어있는지를 저장하는 배열 초기와
   for (int i = 0;i < 501;i++) {
      exitNode[i] = false;
      real_node[i] = 0;
   }

   //출구노드 갱신, 노드가 몇개의 출구와 연결되어 있는지의 정보 갱신
   for (int i = 0; i < e; i++)
   {
      cin >> ei;
      exitNode[ei] = true;
      for (int j = 0; j < 501; j++)
      {
         if (edge[ei][j] == 1)
         {
            real_node[j]++;
         }
      }
   }
}

int shortest_path(int start_point, int end_point)
{
   //방문여부 확인과 출발점에서의 거리 정보 초기화
   for (int i = 0; i < 501; i++)
   {
      visited[i].det_bool = false;
      visited[i].distance_ = -1;
   }

   //큐에 시작점으로 시작점의 정보를 담는다.
   pos temp;
   temp.pre_node = start_point;
   temp.node = start_point;
   q.push(temp);

   //시작점을 방문하였기 때문에 방문여부 true로 바꾸고 거리는 0으로 함
   visited[start_point].det_bool = true;
   visited[start_point].distance_ = 0;
   //bfs수행
   while (!q.empty())
   {
      pos cur = q.front();
      q.pop();
      if (cur.node == end_point)
      {
         temp_out = cur.pre_node;
      }
      for (int i = 0; i < 501; i++)
      {
         //방문할 노드가 간선정보가 존재하고 아직 방문을 안했으면 큐에담고 부모노드의 거리정보에 +1한다.
         if ((edge[cur.node][i] == 1) && (!visited[i].det_bool))
         {
            temp.pre_node = cur.node;
            temp.node = i;
            q.push(temp);
            visited[i].det_bool = true;
            visited[i].distance_ = visited[cur.node].distance_ + 1;
         }
      }

   }

   return visited[end_point].distance_;
}