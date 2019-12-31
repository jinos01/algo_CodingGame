#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void init();
int n, l, e, ei, si, n1, n2;

//�湮���ο� ��߳�忡�� ������������ �Ÿ� ������ �����ϱ� ���� pi�̸��� ����ü
typedef struct pi
{
   bool det_bool;
   int distance_;
};
//pi������ ��� �迭 
pi visited[501];

//�������� �迭
int edge[501][501];

//�ڽŰ� �θ����� ������ ������ pos�̸��� ����ü
typedef struct pos {
   int node;
   int pre_node;
}pos;

//��尡 ��� �ⱸ�� ����Ǿ��ִ����� �����ϴ� �迭
int real_node[501];

//�ⱸ��� �迭
bool exitNode[501];

//pos������ queue ����
queue<pos> q;

//shortest_path�Լ��� ������ �� ��������� �θ��� ������ �����ϴ� temp_out, ���� ��� ��� ������ ��� output_
int temp_out, output_;

//���� ��� ������ �ִܰŸ� ����Լ� >> bfs���
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
            //�ⱸ���� �Է��� si�������� �ִܰ�θ� ���Ѵ�.
            int shortest1 = shortest_path(si, i);

            //�ִܰ���� �ּڰ��� ���Ͽ� �� ���� �ⱸ���� �� �ⱸ����� �θ��带 �����Ѵ�.
            if ((shortest1 < min) && (shortest1 > 0))
            {
               min = shortest1;
               exit_info = i;
               output_ = temp_out;
            }
         }
      }

      //�ִܰ���� �ּڰ��� 1�̶�� ���� �ٷ� ������ �湮�� ��尡 �ⱸ��� ���̹Ƿ� �ⱸ���� �� �ⱸ����� �θ��忡 �ش��ϴ� ���������� �����Ѵ�.
      if (min == 1)
      {
         //���� �ⱸ�� ��� �������� ����
         edge[si][exit_info] = 0;
         edge[exit_info][si] = 0;
         real_node[si]--;
         cout << si << " " << exit_info << endl;
      }

      //�ִܰ���� �ּڰ��� 1�� �ƴ϶�� ���� ���� ������ �����Ƿ� �̸� �ٸ� ���������� �����Ѵ�.
      else
      {
         int min = 1000;
         for (int i = 0; i < 501; i++)
         {
            if (exitNode[i] == true)
            {   
               //�ⱸ��� 2���� ����Ǿ��ִ� ����� ������ �켱������ �����ϱ� ���� �ִܰ�θ� �ٽ� ���Ѵ�.
               int shortest2 = shortest_path(si, i);
               if ((shortest2 < min) && (real_node[temp_out] == 2) && (shortest2 > 0))
               {
                  min = shortest2;
                  exit_info = i;
                  output_ = temp_out;
               }
            }
         }

         //�� ������ �ش��ϴ� ��� ���� ����
         edge[exit_info][output_] = 0;
         edge[output_][exit_info] = 0;
         real_node[output_]--;
         cout << exit_info << " " << output_ << endl;
      }
   }

}

//��κ��� �Է������� �޴� �Լ�
void init()
{
   cin >> n >> l >> e; cin.ignore();
   //�����迭 �ʱ�ȭ
   for (int i = 0; i < 501;i++)
   {
      for (int j = 0; j < 501; j++)
      {
         edge[i][j] = 0;
      }
   }

   //�������� ����
   for (int i = 0; i < l; i++)
   {
      cin >> n1 >> n2;
      edge[n1][n2] = 1;
      edge[n2][n1] = 1;
   }

   //�ⱸ��带 �����ϴ� �迭�� ��尡 ��� �ⱸ�� ����Ǿ��ִ����� �����ϴ� �迭 �ʱ��
   for (int i = 0;i < 501;i++) {
      exitNode[i] = false;
      real_node[i] = 0;
   }

   //�ⱸ��� ����, ��尡 ��� �ⱸ�� ����Ǿ� �ִ����� ���� ����
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
   //�湮���� Ȯ�ΰ� ����������� �Ÿ� ���� �ʱ�ȭ
   for (int i = 0; i < 501; i++)
   {
      visited[i].det_bool = false;
      visited[i].distance_ = -1;
   }

   //ť�� ���������� �������� ������ ��´�.
   pos temp;
   temp.pre_node = start_point;
   temp.node = start_point;
   q.push(temp);

   //�������� �湮�Ͽ��� ������ �湮���� true�� �ٲٰ� �Ÿ��� 0���� ��
   visited[start_point].det_bool = true;
   visited[start_point].distance_ = 0;
   //bfs����
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
         //�湮�� ��尡 ���������� �����ϰ� ���� �湮�� �������� ť����� �θ����� �Ÿ������� +1�Ѵ�.
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