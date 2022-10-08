#include<iostream>
#include<vector>
#include<queue>
#include<limits>

using namespace std;

class MazeRunner{
public:
    using Cell=pair<int,int>;
    int m,n;
    vector<string>Grid;

    vector<vector<int>>m_distance;
    vector<vector<Cell>>m_parent;
    const Cell unvisited_block={-1,-1};
    Cell start,goal;

    MazeRunner(istream&in){
        string maze_r;
        in>>m>>n;
        getline(in,maze_r);
        //takes in maze row by row and pushes on to grid
        for(int r=0;r<m;r++){
            getline(in,maze_r);
            Grid.push_back(maze_r);

            /*creates a temporary object which will then be pushed
             into container*/
            m_parent.emplace_back(n,unvisited_block);
            m_distance.emplace_back(n,numeric_limits<int>::max());

            //locates starting point
            auto neighbour=maze_r.find('S');
            if(neighbour!=maze_r.npos){
                start.first =r;
                start.second=neighbour;
            }
            // locates the goal
            neighbour=maze_r.find('G');
            if(neighbour!=maze_r.npos){
                goal.first =r;
                goal.second=neighbour;
            }
        }
    }

    int&distance(Cell&pos){
        return m_distance[pos.first][pos.second];
    }

    Cell&parent(Cell&pos){
        return m_parent[pos.first][pos.second];
    }

    bool unvisited(Cell&pos) {
        return parent(pos)==unvisited_block;
    }

    bool valid(Cell&pos){
        if(pos.first>=0&&pos.first<m
           &&pos.second>=0&&pos.second<n){
            return Grid[pos.first][pos.second]==' '
                || Grid[pos.first][pos.second]=='.'
                || Grid[pos.first][pos.second]=='G';
        }
        else{
            return false;
        }
    }

    void BFS(){
        queue<Cell>q;

        Cell curr,neighbour;
        m_distance[start.first][start.second]=0;
        m_parent[start.first][start.second]={-2,-2};

        q.push(start);

        while(!q.empty()&&unvisited(goal)){
            curr=q.front();
            q.pop();

            /*checks all 4 neighbours if they are valid and unvisted
            if True then pushes to q*/
            
            //down neighbour
            neighbour={curr.first+1,curr.second};
            if(valid(neighbour)&&unvisited(neighbour)){
                m_distance[neighbour.first][neighbour.second]=m_distance[curr.first][curr.second]+1;
                m_parent[neighbour.first][neighbour.second]=curr;
                q.push(neighbour);
            }

            //left neighbour
            neighbour={curr.first,curr.second-1};
            if(valid(neighbour)&&unvisited(neighbour)){
                m_distance[neighbour.first][neighbour.second]=m_distance[curr.first][curr.second]+1;
                m_parent[neighbour.first][neighbour.second]=curr;
                q.push(neighbour);
            }

            //up neighbour
            neighbour={curr.first-1,curr.second};
            if(valid(neighbour)&&unvisited(neighbour)){
                m_distance[neighbour.first][neighbour.second]=m_distance[curr.first][curr.second]+1;
                m_parent[neighbour.first][neighbour.second]=curr;
                q.push(neighbour);
            }

            //right neighbour
            neighbour={curr.first,curr.second+1};
            if(valid(neighbour)&&unvisited(neighbour)){
                m_distance[neighbour.first][neighbour.second]=m_distance[curr.first][curr.second]+1;
                m_parent[neighbour.first][neighbour.second]=curr;
                q.push(neighbour);
            }
        }

        if(q.empty()&&unvisited(goal)){
            cout<<"No Path"<<endl;
        }
        else{
            curr=m_parent[goal.first][goal.second];
            while(curr!=start){
                Grid[curr.first][curr.second]='*';
                curr=m_parent[curr.first][curr.second];
            }
            for(const string&maze_r : Grid){
            cout<<maze_r<<endl;
        }
        }
    }
};

int main()
{
    MazeRunner x(cin);
    x.BFS();
    return 0;
}

