//FINAL CODE WITH ALL PATH DISPLAYED WITH ORIGINAL REQUIREMENTS 

#include<iostream>
#include<list>
#include<fstream>
#include<cstdlib>


int p[999][999],a[999][999],DCN[99][99];
int flow[999][999];
int array[999], temp[999];
int c=0;
float TCAMsize[20];
int count=0;

using namespace std;


// the given funcion finds the shortest path for a given flow with minimum number of activated switch

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

// display() function gives the details of the number of switch which are activated

void display()
{
	int l,i,j,k,n=999;
    cout<<"Display of the switches which are activated : \n";

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


// path() function used to display the path for the given flow
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


//counting() function subtracts the given flow value from each edge it is passing through from the DCN matrix

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



// minimumpathcapacity() function is used to return the value of pathcapacity

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


// minimumpathTCAM() function used to return the pathTCAM value

int minimumpathTCAM()
{
	int i;
	float tempvar;

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
          
      
      cout<<endl;
   
  return tempvar;
}

// to find all path for the source and destination


class Graph
{
    int V;  // number of vertices in the graph
    list<int> *adj;  // pointer to the array containing agjacency list 
    
    void printAllPathsUtil(int , int , bool [], int [], int );  // a recursive function used by printAllPath() function to display all path
 
public:
	
    Graph(int V);  // a constructor of the class Graph    
    void addEdge(int u, int v);  // function used to add edges 
    void printAllPaths(int s, int d);   // to print all the path of the given source and destination   
	 
};

// constructor of the class Graph explicitly defined

Graph::Graph(int V)    
{
    this->V = V;
    adj = new list<int>[V];
}

// addEdge() function used to add edge to the list

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);  // add v to u's list
}

// printAllPaths() function used to display the path from u to v

void Graph::printAllPaths(int s, int d)
{
    bool *visited = new bool[V];     // creating an array to keep track if a node is visited or not
    int *path = new int[V];         // creating an array to store the path as index    
    int path_index = 0;            // initializing all path as empty     
    
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;       // initializing all vertices as not visited
    }
    
    printAllPathsUtil(s, d, visited, path, path_index);
}

// recursive function used ny printAllPath() function

void Graph::printAllPathsUtil(int u, int d, bool visited[], int path[], int path_index)
{
    visited[u] = true;
    path[path_index] = u;
    
     // condition when the current vertex is the destination 
    
    if (u == d)
    {
        for (int i = 0; i<=path_index; i++)
            cout << path[i] << "-> ";
        cout << endl;
    }
    
      // when the current vertex is not destination
      
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
	
    int i,j,min,k,n,m,l,sw,x,y,z,ch;
    float pathCapacity,pathTCAM;
     ifstream input1;
     ifstream input2;
     ifstream input3;
     ifstream input4;
     ifstream input5;
    input1.open("F:\\dcnInput8.txt");
    input2.open("F:\\flowMatrix4.txt");
    input3.open("F:\\switch.txt");
    input4.open("F:\\copy.txt");
    input5.open("F:\\flowMatrix16.txt");
    
    cout<<endl;
	cout<<"\n---Energy Efficient Model for SDN---"<<endl;
    cout<<"================================================="<<endl;
	cout<<"\n 1. For 8 node DCN graph Model ";
    cout<<"\n 2. For 36 node DCN graph Model";
    cout<<"\n 3. User Choice Model";
    cout<<"\n 4. Exit"<<endl;
    cout<<"================================================="<<endl;
    cout<<"Enter User Choice........"<<endl;
    cin>>ch;
    
     // selection according to the user preferences
     
    switch(ch)  
    {
    	// for 8 node DCN graph model
    	case 1:
    		n=8;
    		m=4;
    		sw=4;
    			for(i=0;i<n;i++)
				{
        			for(j=0;j<n;j++)
	    			{
	    				//read from file dcnInput8.txt
                 		input1 >> a[i][j];
            		}
    			}
				
			    for(i=0;i<m;i++)
      			{
        			for(j=0;j<m;j++)
    	      		{
    	      			//read from file flowMatrix4.txt
    		       	input2 >> flow[i][j];
		      		}
	  			}
	  			cout<<"number of switches are  :  "<<sw<<endl;
   			    cout<<" enter the TCAM size of each switches  \n"<<endl;
        		for(z=0;z<sw;z++)
         		 {
         		 	//read from file switch.txt
    	     			input3 >>TCAMsize[z];
	      		}
    		break;
    		
    	// for 36 node DCN graph model
    	case 2:
			n=36;
    		m=16;
    		sw=20;
    		//-----------DCN GRAPH READ FROM FILE------------//
				for(i=0;i<n;i++)
				{
        			for(j=0;j<n;j++)
	    			{
	    			   input4 >> a[i][j];
            		}
    			}
    		//------Tcam size  read---------------//
    		 		
				cout<<"\n Enter the flow demand matrix\n"<<endl;
  
			    for(i=0;i<m;i++)
      			{
        			for(j=0;j<m;j++)
    	      		{
    	      		  	input5 >> flow[i][j];
		      		}
	  			}
	  			
            // display of TCAM size of each switch
            
                cout<<"number of switches are  :  "<<sw<<endl;
   			    cout<<" enter the TCAM size of each switches  \n"<<endl;
        		for(z=0;z<sw;z++)
         		 {
    	     			TCAMsize[z]=250+rand()%1001;
    	     		//	TCAMsize[z]=TCAMsize[z]/1024;
	      		 }
    		break;
    		
    		// according to user preferences
    		
    	case 3:
		 

    			cout<<"Enter the number of nodes for DCN matrix : \n";
    			cin>>n;
    			
    			// DCN Graph as iput from user
    			
			    cout<<"enter the cost matrix\n";

    			for(i=0;i<n;i++)
				{
        			for(j=0;j<n;j++)
	    			{
                 		cin>>a[i][j];
            		}
    			}

    			
    			cout<<"Enter the number of node of flow matrix: \n";
    			cin>>m;
    			
    			// the TCAM size of each switch input from user 
    			
    			cout<<"Enter the number of switches\n";
    			cin>>sw;
    			cout<<"number of switches are  :  "<<sw<<endl;
   			    cout<<" enter the TCAM size of each switches  \n"<<endl;
        		for(z=0;z<sw;z++)
         		 {
    	     			cin>>TCAMsize[z];
	      		}
	      		
	      		// flow demand matrix input from user 
	      		
				cout<<"\n Enter the flow matrix\n"<<endl;
  
    		for(i=0;i<m;i++)
      		{
        		for(j=0;j<m;j++)
    	      {
    		       cin>>flow[i][j];
		      }
	  		}
	
		        
    		break;
    	default:
    		exit(0);
	}
	
	// display of the details of the TCAM size of each switch
	
	cout<<"Display of the TCAM size of each switch\n"<<endl;
	
     	for(z=0;z<sw;z++)
        	{
		        cout<<"TCAM size of switch  : "<<z+1<<" is "<<TCAMsize[z]<<"MB"<<endl;
		
        	}
        	
	 cout<<endl;
	 
	 // Display of the DCN graph
	 
     cout<<"Display of the DCN Graph in the form of matrix\n"<<"\n------------------------------------------------------------------"<<endl;
     cout<<"Node";
      for(i=0;i<n;i++)
    cout<<"\t"<<i<<"|";
    cout<<"\n------------------------------------------------------------------"<<endl;
     for(i=0;i<n;i++)
	 {
	 	cout<<"Node "<<i<<"\t";
        for(j=0;j<n;j++)
	    	{
		    	DCN[i][j]=a[i][j];
                cout<<a[i][j]<<"\t ";
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

  cout<<endl;
  
  // display of the flow demand matrix
  
  cout<<"\nFlow matrix information \n"<<"\n---------------------------------"<<endl;
  cout<<"Node";
    for(i=0;i<m;i++)
    cout<<"\t"<<i<<"|";
    cout<<"\n---------------------------------"<<endl;
    
	for(i=0;i<m;i++)
    {	cout<<"Node "<<i<<"\t";
    	for(j=0;j<m;j++)
    	  {
    		   cout<<flow[i][j]<<"\t";
	   	  }
    	cout<<endl;
	}


// graph representation in the form of adjacency list for 8 node DCN graph

	Graph q(8);
	 q.addEdge(0,2); q.addEdge(0,3);
	 q.addEdge(2,0); q.addEdge(3,0);
	 q.addEdge(1,3); q.addEdge(2,4);
	 q.addEdge(3,1); q.addEdge(4,2);
	 q.addEdge(2,5); q.addEdge(3,6);
	 q.addEdge(5,2); q.addEdge(6,3);
	 q.addEdge(3,7); q.addEdge(7,3);

// graph representation in the form of adjacency list for 36 node DCN graph

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
	   	
	   	   source = x+sw;
           destination = y+sw;
          if(x!=y)
	        {
                     
                     demand=flow[x][y];
                     
                     // to find all path for the given flow
                     
                     cout<<"-------------------------------------------------------------------------------"<<endl;
                     cout<<"\nFor the flow demand value "<<demand<<" from source "<<source<<" to destination "<<destination<<endl;
                     if(ch==1)
                     {
                     cout << "Following are all different paths from " << source << " to " << destination << endl;
                     
                     q.printAllPaths(source,destination);
                     }
                     else if(ch==2 && flow[x][y]!=0)
                     {
                     	cout << "Following are all different paths from " << source << " to " << destination << endl;
                     g.printAllPaths(source,destination);	
					 }
                    
                     cout<<endl;
                     
                     // to find the shortest path for the given flow with minimum number of newly activated switch
                     
                 if(flow[x][y]!=0)
				   { 
                     cout<<"Shortest path cost between the vertices "<<source<<" and " <<destination<<" : "<<a[source][destination]<<endl;
   
                     cout<<"Path : ";
                     cout<<source<<"-->";
                     count=0;

                     path(source,destination);
    
                     cout<<destination<<endl<<endl;

                     counting(source,destination,demand);

                     cout<<"\n The number of intermediate switch is \n"<<count << endl;
                       
                      cout<<"Display of the DCN Graph in the form of matrix after iteration\n"<<"\n------------------------------------------------------------------"<<endl;
                      cout<<"Node";

                        for(i=0;i<n;i++)
                        cout<<"\t"<<i<<"|";
                        cout<<"\n-----------------------------------------------------------------"<<endl;
    
                           for(i=0;i<n;i++)
	                         {
	                         	cout<<"Node "<<i<<"\t";
                                 for(j=0;j<n;j++)
		                             {
                                          cout<<DCN[i][j]<<" \t";
                                     }
                               cout<<endl;
                             }

                       pathCapacity=minimumpathcapacity(source,destination);
                       pathTCAM=minimumpathTCAM();
 
                       cout<<endl;
                              cout<<" pathcapacity of the given path is : \n"<<pathCapacity<<"GB";
                       cout<<endl;
                              cout<<"value of pathTCAM for the given path: \n"<<pathTCAM<<"GB"<<endl;
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
					cout<<endl;
				}
						  
           }
           else
           cout<<"\n Since the same node from source "<<source<<" destination "<<destination<<" hence no transfer of the data take place\n";
           cout<<endl;

        }
   }
   

cout<<"----------------------------------------------------------------"<<endl;
cout<<endl;
cout<<" final display of the output"<<endl;
cout<<endl;
display();
cout<<"Display of the flow matrix after iteration to check whether all the flow demand is satisfied or not:  \n";
 cout<<"Node";
  for(i=0;i<m;i++)
  cout<<"\t"<<i<<"|";
  cout<<"\n---------------------------------"<<endl;


for(int f=0;f<m;f++)
{
	cout<<"Node "<<f<<"\t";
	for(int g=0;g<m;g++)
	{
		cout<<flow[f][g]<<"\t ";
	}
	cout<<endl;
}

     cout<<"Display of the DCN Graph in the form of matrix\n"<<"\n------------------------------------------------------------------"<<endl;
     cout<<"Node";
      for(i=0;i<n;i++)
    cout<<"\t"<<i<<"|";
    cout<<"\n------------------------------------------------------------------"<<endl;
     for(i=0;i<n;i++)
	 {
	 	cout<<"Node "<<i<<"\t";
        for(j=0;j<n;j++)
	    	{
		    	
                cout<<DCN[i][j]<<"\t ";
            }
        cout<<endl;
     }
     
// closing the open files  
     
input1.close();
input2.close();
input3.close();
input4.close();
input5.close();

    return 0;
}

