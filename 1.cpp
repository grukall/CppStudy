#include <iostream>
#include <queue>

using namespace std;

int main()
{
  //cin.tie(NULL);
  //ios::sync_with_stdio(false);
  int T; cin >> T;

  for (int i = 0; i < T; i++)
  {
    int n; cin >> n;
    priority_queue<int> pq;
    vector<int> v;
    for (int j = 1; j <= n; j++)
    {
      int cn; cin >> cn;
      cin.ignore();
      //cout << "cn = " << cn << '\n';
      pq.push(cn);
      if (j % 2 == 1)
      {
        int midi = pq.size() / 2;
        queue<int> q;
        while (midi > 0)
        {
          q.push(pq.top());
          pq.pop();
          midi -= 1;
        }

        v.push_back(pq.top());

        while (!q.empty())
        {
          pq.push(q.front());
          q.pop();
        }
      }
    }

    cout << v.size() << '\n';
    for (int i = 1; i <= v.size(); i++)
    {
      int val = v[i-1];
      cout << val << ' ';
      if (i % 10 == 0)
        cout << '\n';
    }
    cout << '\n';
  }
}