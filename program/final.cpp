//FINAL CODE WITH ALL PATH DISPLAYED WITH ORIGINAL REQUIREMENTS 

#include<iostream>
#include<list>

int p[999][999],a[999][999],DCN[99][99];
int flow[999][999];
int array[999], temp[999];
int c=0;
int TCAMsize[20];
int count=0;

using namespace std;


void Shortestpath(int n)
{
	  int i,j,k,x,l;

	       for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                     p[i][j]=-1;

       for(l=0;l<999;l++)
	      array[l]=-1;


	  for(k=0;k<n;k++)
	  {
        for(i=0;i<n;i++)
		   {
            for(j=0;j<n;j++)
			  {

                if((a[i][k] + a[k][j])<a[i][j]) 
			    	{

                    a[i][j]=(a[i][k] + a[k][j]);
                    p[i][j]=k;
                    
                    }
                    
               }
           }
      }
}


void display()
{
	int l,i,j,k,n=999;
    cout<<"Display of the number of activated switch : \n";

      for(i=0;i<n;++i)
      {
          for(j=i+1;j<n;)
            {
               if(array[i]==array[j])
                 {
                    for(k=j;k<n-1;++k)
                       array[k]=array[k+1];

                        --n;
                  }
               else
                      ++j;
            }
      }

       for(l=0;l<999;l++)
	     {
            if(array[l]==-1)
			break;
            else
	  	     cout<<array[l]<<" ";
         }

     cout<<endl;
}


void path(int u,int v)
{
    int k;

    k = p[u][v];
    if (k == -1)
        return;

    path(u,k);

    array[c++]=k;
    temp[count++]=k;
    cout<<k<<"-->";

    path(k,v);

}



void counting(int u,int v,int demand)
{
    int i,x,y;
    int flag=0;

    for(i=0;i<count;i++)
   	   {
   		  cout<<temp[i]<<" ";
       }

    cout<<endl;

	 if(count!=0)
	   {
         for(i=0;i<=count;i++)
            {
   	           if(flag==0)
   	              {
	                y=u;
	                flag=1;
            	  }
            	else
                	{
	                 	x=y;
	                 	y=temp[i-1];
		                DCN[x][y]-=demand;
	                }
            }
            
          DCN[temp[count-1]][v]-=demand;

       }
}



int minimumpathcapacity(int u,int v)
{
	int i,tempvar,x,y;
	int flag=0;
	
    	if(count!=0)
	      {
	       	tempvar=999;
            	for(i=0;i<=count;i++)
                 {
                   	if(flag==0)
                    	{
	                       y=u;
	                       flag=1;	
	                    }
	                else
	                    {
	                    	x=y;
	                    	y=temp[i-1];
	
	                        	if(a[x][y]<=tempvar)
	                            	{
			                           tempvar=a[x][y];
	                            	}
		
	                    }
                 }
                 
             if(a[temp[count-1]][v]<=tempvar)
               {
       	
                   tempvar=a[temp[count-1]][v];
   
               }
          }
          else
                    tempvar=a[u][v];

	return tempvar;
}



int minimumpathTCAM()
{
	int i,tempvar;

	   if(count!=0)
	      {
	          	tempvar=999;
	             for(i=0;i<count;i++)
                   	{
	                	if(TCAMsize[temp[i]]<=tempvar)
	                      	{
			                   tempvar=TCAMsize[temp[i]];
	    	                }
    	            }
          }
       else
          {
               tempvar=0;
          }
          
      cout<<"final value of temp\n"<<tempvar;
      cout<<endl;
   
  return tempvar;
}

// to find all path for the source and destination


class Graph
{
    int V;  
    list<int> *adj;   
    
    void printAllPathsUtil(int , int , bool [], int [], int );
 
public:
	
    Graph(int V);     
    void addEdge(int u, int v);     
    void printAllPaths(int s, int d);   
	 
};


Graph::Graph(int V)    
{
    this->V = V;
    adj = new list<int>[V];
}



void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);  
}



void Graph::printAllPaths(int s, int d)
{
    bool *visited = new bool[V];   
    int *path = new int[V];       
    int path_index = 0;         
    
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;      
    }
    
    printAllPathsUtil(s, d, visited, path, path_index);
}



void Graph::printAllPathsUtil(int u, int d, bool visited[], int path[], int path_index)
{
    visited[u] = true;
    path[path_index] = u;
    
    
    
    if (u == d)
    {
        for (int i = 0; i<=path_index; i++)
            cout << path[i] << "-> ";
        cout << endl;
    }
    
    else
    {
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index+1);
    }
    
    visited[u] = false;
}

// to find the all path ends here


int main()
{
	
    int i,j,min,k,n,m,l,sw,x,y,z;
    int pathCapacity,pathTCAM;
    
    cout<<"Enter the number of nodes for DCN matrix : \n";
    cin>>n;
    cout<<"Enter the number of node of flow matrix: \n";
    cin>>m;
    cout<<"Enter the number of switches\n";
    cin>>sw;
    cout<<"number of switches are  :  "<<sw<<endl;
    
    cout<<" enter the TCAM size of each switches  \n"<<endl;
        for(z=0;z<sw;z++)
          {
    	     cin>>TCAMsize[z];
	      }
	
	cout<<"Display of the TCAM size of each switch\n"<<endl;
	
     	for(z=0;z<sw;z++)
        	{
		        cout<<"TCAM size of switch  : "<<z+1<<" is "<<TCAMsize[z]<<endl;
		
        	}
	
    cout<<"enter the cost matrix\n";

    for(i=0;i<n;i++)
	{
        for(j=0;j<n;j++)
	    	{
                 cin>>a[i][j];
            }
    }

     cout<<"Display of the cost matrix\n"<<endl;
     
     for(i=0;i<n;i++)
	 {
        for(j=0;j<n;j++)
	    	{
		    	DCN[i][j]=a[i][j];
                cout<<a[i][j]<<" ";
            }
        cout<<endl;
     }

   for(i=0;i<n;i++)
   {
        for(j=0;j<n;j++)
		  {
            if(a[i][j]==0)
            a[i][j]=9999;
          }
   }

  cout<<"Display of the DCN matrix\n"<<endl;
  
     for(i=0;i<n;i++)
	 {
        for(j=0;j<n;j++)
		  {
              cout<<DCN[i][j]<<" ";
          }
        cout<<endl;
     }

  cout<<"\n Enter the flow matrix\n"<<endl;
  
    for(i=0;i<m;i++)
      {
        	for(j=0;j<m;j++)
    	      {
    		       cin>>flow[i][j];
		      }
	  }

  cout<<"\nDisplay the flow matrix\n"<<endl;
  
    for(i=0;i<m;i++)
    {
    	for(j=0;j<m;j++)
    	  {
    		   cout<<flow[i][j]<<" ";
	   	  }
    	cout<<endl;
	}


// graph representation in the form of adjacency list
	
	 Graph g(36);
	 
	 g.addEdge(0,4); g.addEdge(0,6); g.addEdge(0,8); g.addEdge(0,10);
	 g.addEdge(4,0); g.addEdge(6,0); g.addEdge(8,0); g.addEdge(10,0);
	  
	 g.addEdge(1,4); g.addEdge(1,6); g.addEdge(1,8); g.addEdge(1,10);
	 g.addEdge(4,1); g.addEdge(6,1); g.addEdge(8,1); g.addEdge(10,1);
	 
	 g.addEdge(2,5); g.addEdge(2,7); g.addEdge(2,9); g.addEdge(2,11);
	 g.addEdge(5,2); g.addEdge(7,2); g.addEdge(9,2); g.addEdge(11,2);
	 
	 g.addEdge(3,5); g.addEdge(3,7); g.addEdge(3,9); g.addEdge(3,11);
	 g.addEdge(5,3); g.addEdge(7,3); g.addEdge(9,3); g.addEdge(11,3);
	 
	 g.addEdge(4,13); g.addEdge(4,12); g.addEdge(5,13); g.addEdge(5,12);
	 g.addEdge(13,4); g.addEdge(12,4); g.addEdge(13,5); g.addEdge(12,5);
	 
	 g.addEdge(6,14); g.addEdge(6,15); g.addEdge(7,14); g.addEdge(7,15);
	 g.addEdge(14,6); g.addEdge(15,6); g.addEdge(14,7); g.addEdge(15,7);
	 
	 g.addEdge(8,16); g.addEdge(8,17); g.addEdge(9,16); g.addEdge(9,17);
	 g.addEdge(16,8); g.addEdge(17,8); g.addEdge(16,9); g.addEdge(17,9);
	 
	 g.addEdge(10,18); g.addEdge(10,19); g.addEdge(11,18); g.addEdge(11,19);
	 g.addEdge(18,10); g.addEdge(19,19); g.addEdge(18,11); g.addEdge(19,11);
	 
	 g.addEdge(12,20); g.addEdge(12,21); g.addEdge(13,22); g.addEdge(13,23);
	 g.addEdge(20,12); g.addEdge(21,12); g.addEdge(22,13); g.addEdge(23,13);
	 
	 g.addEdge(14,25); g.addEdge(14,24); g.addEdge(15,27); g.addEdge(15,26);
	 g.addEdge(25,14); g.addEdge(24,14); g.addEdge(27,15); g.addEdge(26,15);
	 
	 g.addEdge(16,29); g.addEdge(16,28); g.addEdge(17,31); g.addEdge(17,30);
     g.addEdge(29,16); g.addEdge(28,16); g.addEdge(31,17); g.addEdge(30,17);
	 
	 g.addEdge(18,32); g.addEdge(18,33); g.addEdge(19,34); g.addEdge(19,35);
	 g.addEdge(32,18); g.addEdge(33,18); g.addEdge(34,19); g.addEdge(35,19);
	 
	
Shortestpath(n);

int source,destination,demand;

for(x=0;x<m;x++)
   {
    for(y=0;y<m;y++)
	   {
	   	
          if(x!=y)
	        {
                     source = x+20;
                     destination = y+20;
                     demand=flow[x][y];
                     
                     cout << "Following are all different paths from " << source << " to " << destination << endl;
                     
                     g.printAllPaths(source,destination);
                     
                     cout<<endl;
                     
                 if(flow[x][y]!=0)
				   { 
                     cout<<"Shortest path cost between the vertices "<<source<<" and " <<destination<<" : "<<a[source][destination]<<endl;
   
                     cout<<"Path : ";
                     cout<<source<<"-->";
                     count=0;

                     path(source,destination);
    
                     cout<<destination<<endl<<endl;

                     counting(source,destination,demand);

                     cout<<"\n the value of count is \n"<<count << endl;


                     cout<<"\n Display of the DCN matrix after iteration\n";

                           for(i=0;i<n;i++)
	                         {
                                 for(j=0;j<n;j++)
		                             {
                                          cout<<DCN[i][j]<<" ";
                                     }
                               cout<<endl;
                             }

                       pathCapacity=minimumpathcapacity(source,destination);
                       pathTCAM=minimumpathTCAM();
 
                       cout<<endl;
                              cout<<" pathcapacity of the given path is : \n"<<pathCapacity;
                       cout<<endl;
                              cout<<"value of pathTCAM for the given path: \n"<<pathTCAM<<endl;
                       cout<<endl;
                       
                       if(pathCapacity==0 || pathTCAM==0)
                          {
                       	    continue;
					      }
					    if(pathCapacity >= flow[x][y])
					      {
					    	flow[x][y]=0;
						  }
						else
						  {
						  	flow[x][y]=flow[x][y]-pathCapacity;
						  }
				}
				else
				{
					cout<<"Flow Demand is zero so shortest path is not required to transfer data from source "<<source<<" to destination  "<<destination;
				}
						  
           }

        }
   }
   
display();

cout<<"Display of the flow matrix after iteration to check whether all the flow demand is satisfied or not:  \n";

for(int f=0;f<m;f++)
{
	for(int g=0;g<m;g++)
	{
		cout<<flow[f][g]<<" ";
	}
	cout<<endl;
}


    return 0;
}

