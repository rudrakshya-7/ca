#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
int n,i,j,r=0,k=0,q2=0,t,flag,flag1;
void roundrobin();
void preemptive();
void secondsort();
typedef struct Process
{
    int pid, burstt,arrivalt,ppriority,startt,endt,waitingt;

}process;
process p[200],q1[200],q3[200];//q1,q3 to store process in queue
//++++++++++++++++++++++++++++++++++++++&&&&&&&&&&&&&&&&&&&SORTING&&&&&&&&&&&&&&&&&&&++++++++++++++++++++++++++++++++++++++++++++++++
void Arrival_Time_Sorting()
{

      process temp;
      for(i = 0; i < n - 1; i++)
      {
            for(j = i + 1; j < n; j++)
            {
                  if(p[i].arrivalt> p[j].arrivalt)
                  {
                        temp = p[i];
                        p[i] = p[j];
                        p[j] = temp;
                  }
            }
      }
      int s;
      for(s=0;s<n;s++)
      {
          //if two have same arrivaltime and next have higher priority
          if(p[s].arrivalt==p[s+1].arrivalt&&p[s].ppriority>p[s+1].ppriority)
            {
                temp = p[s+1];
                p[s+1] = p[s];
                p[s] = temp;
            }
      }
}
void secondsort()
{
    process temp1;
    for(i = 0; i < n - 1; i++)
      {
            for(j = i + 1; j < n; j++)
            {
                  if(p[i].ppriority> p[j].ppriority)
                  {
                        temp1 = p[i];
                        p[i] = p[j];
                        p[j] = temp1;
                  }
                  if(q3[i].ppriority> q3[j].ppriority)
                  {
                        temp1 = q3[i];
                        q3[i] = q3[j];
                        q3[j] = temp1;
                  }
            }
      }
}
void preemptive()
{
    int c=n,a=0,flag=0;
    t=p[0].arrivalt;
   while(t>=0&&c>0)
   {
       //printf("We are at beginning of while loop\n");
        if (p[k].arrivalt < p[k+1].arrivalt&&p[k].burstt>0)
           {
               if(p[k].burstt==q3[k].burstt)
                        q3[k].startt=t;
               printf("Process P%d is Running at time %d with priority %d \n",p[k].pid,t,p[k].ppriority);
               p[k].burstt=p[k].burstt-1;
               if(p[k].burstt==0&&p[k+1].ppriority < p[k].ppriority&&p[k+1].arrivalt > p[k].arrivalt&&p[k+1].arrivalt==t)
                {
                    k=k+1;
                    c--;
                    q3[k].endt=t;
                }
                else if(p[k].burstt==0)
                    {c--;
                    q3[k].endt=t;
                    }
           }

        else if (p[k].arrivalt == p[k+1].arrivalt && p[k].ppriority < p[k+1].ppriority&&p[k].burstt>0)
                {

                    if(p[k].burstt==q3[k].burstt)
                        q3[k].startt=t;
                    printf("Process P%d is Running at time %d with priority %d \n",p[k].pid,t,p[k].ppriority);
                    p[k].burstt=p[k].burstt-1;
                    if(p[k].burstt==0)
                       {
                          c--;
                          q3[k].endt=t;
                       }
                }
        else if(k==n-1&&p[k].burstt>0)//since if 2 process is present then first will execute and last will be left out
            {
                if(p[k].burstt==q3[k].burstt)
                        q3[k].startt=t;
                printf("Process P%d is Running at time %d with priority %d \n",p[k].pid,t,p[k].ppriority);
                p[k].burstt=p[k].burstt-1;
                if(p[k].burstt==0)
                 {c--;
                 q3[k].endt=t;
                 }
                 if(c!=n-1&&c!=0&&p[k].burstt==0||(c==1&&p[k].burstt==0))//if processes are left due to lower priority but not preempted then here....
                 {
                     int l,m;
                     for(l=0;l<n;l++)
                        {
                            secondsort();
                            if(p[l].burstt==q3[l].burstt)
                            {
                                for(m=0;p[l].burstt>0;m++)
                            {
                                t++;
                                if(p[l].burstt==q3[l].burstt)
                                        q3[l].startt=t;
                                printf("Process P%d is running at time %d with priority %d\n",p[i].pid,t,p[i].ppriority);
                                p[l].burstt=p[l].burstt-1;
                                if(p[l].burstt==0)
                                {
                                    q3[l].endt=t;
                                    c--;
                                }
                            }
                            }
                        }
                        c=0;
                 }
            }
            else if(c!=0&&c!=n-1)//problem......in case when cpu is idle it will decrement c and increment k but i need help
                {
                    flag1=1;
                    roundrobin();
                    if(p[k+1].ppriority<p[k].ppriority&&p[k].arrivalt>=t)//should be taken into consideration
                    k=k+1;
                    if(k!=n-1&&p[k].arrivalt>t)
                        {
                            t=p[k].arrivalt;
                            t--;
                        }
                }
            ++t;
            for(a=k+1;a<n;a++)//checking if another process has come at that particular time
            {
                if(p[a].arrivalt==t&&flag==0)//flag to check there is no two process with same arrival time donot alter k value
               {
                if(p[a].ppriority < p[k].ppriority&&p[a].arrivalt > p[k].arrivalt||(p[a].ppriority==p[k+1].ppriority||p[a].ppriority==p[k].ppriority)&&p[a].arrivalt>p[k+1].arrivalt)//||p[a].arrivalt>p[k].arrivalt)//if priority and arrival time both are same
                   {
                       if(p[k].burstt>0)
                       {
                       q1[q2]=p[k];
                       q2++;
                       r++;
                       c--;
                       }
                       k=a;
                       flag=1;
                   }
               }
            }
            flag=0;
   }
}
//++++++++++++++++++++++++++++++++++++++&&&&&&&&&&&&&&&ROUND_ROBIN&&&&&&&&&&&&&+++++++++++++++++++++++++++++++++++++++++++++++++++
void roundrobin()
{
    int f=0,f1=0,r1=0,d=0,d1=0,x=r,w=0,flag2=0;
    if(flag1==1)
     while(t>0&&x>0&&p[k+1].arrivalt>t&&flag2==0)
    {
        if(flag2==0)
                {
                    if(q1[r1].burstt>0)
                    {
                    printf("Queue1 Process P%d is running at time %d with priority %d\n",q1[r1].pid,t,q1[r1].ppriority);
                    q1[r1].burstt=q1[r1].burstt-1;
                    t++;
                    if(p[k+1].arrivalt==t)
                        {flag2==1;
                        t=p[k+1].arrivalt;
                            t--;
							goto b;
							}

                    if(q1[r1].burstt==0)
                      {
                          for(w=0;w<n;w++)
                          {
                              if(q3[w].pid==q1[r1].pid)
                                q3[w].endt=t-1;
                          }
                         x--;
                         if(x==0)
                            r--;
                         //printf("value of r %d \n",x);
                      }
                    }
                    ++f;
                    if(f>=2)
                    {
                        if(r1<x)//less than x becz
                            ++r1;
                        else
                            r1=0;
                        f=0;
                    }
                }
    }

     if(flag1==0)
       while(t>0&&r>0)
    {
            if(flag2==0)
                {
                    if(q1[r1].burstt>0)
                    {
                    printf("Process P%d is running at time %d with priority %d\n",q1[r1].pid,t,q1[r1].ppriority);
                    q1[r1].burstt=q1[r1].burstt-1;
                    t++;
                    if(q1[r1].burstt==0)
                    {
                         for(w=0;w<n;w++)
                          {
                              if(q3[w].pid==q1[r1].pid)
                                q3[w].endt=t-1;
                          }
                        r--;
                    }
                    }
                    ++f1;
                    if(f1>=2)
                    {
                        if(r1<r)
                            ++r1;
                        else
                            r1=0;
                        f1=0;
                    }
                }
    }
    b: printf("");
}
//++++++++++++++++++++++++++++++++++++++&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&++++++++++++++++++++++++++++++++++++++++++++++++
int main()
{

    printf("\t\t====================================================================================================\n");
    printf("\t\t\t\t~~~~~~~~~~~~********MULTILEVEL QUEUE SCHEDULING ********~~~~~~~~~~~~ \n");
    printf("\t\t====================================================================================================\n");
    printf("Enter the no.of process\n");
    scanf("%d",&n);
    for(i =0;i<n;i++)
    {
    y: fflush(stdin);
        printf("Enter Process %d: \n",i);
        printf("Enter Burst Time In Multiples Of 2: (for e.g. 2,4...etc)\n");
        scanf("%d",&p[i].burstt);
        if(p[i].burstt%2!=0||p[i].burstt==1)
            goto y;
        printf("Arrival Time:\n");
        scanf("%d",&p[i].arrivalt);
        printf("Priority:\n");
        scanf("%d",&p[i].ppriority);
        p[i].pid=i;


    }
    Arrival_Time_Sorting();//arrival time sorting
    for(i=0;i<n;i++)
    {
        q3[i]=p[i];
    }
     for(i=0;i<n;i++)
    {
        printf("Process P%d: Bursst %d Arrivalt:%d Ppriority:%d and Process id P%d\n",i+1,p[i].burstt,p[i].arrivalt,p[i].ppriority,p[i].pid);
    }

    preemptive();
    int x1=r;
    flag1=0;
    roundrobin();
    int z=0,totalburst;
    float turnaroundt,avgwaiting=0.0;
    for(z=0;z<n;z++)
    {
        //printf("Process P%d: endt %d startt:%d bursst:%d and process id P%d\n",z+1,q3[z].endt,q3[z].startt,q3[z].burstt,q3[z].pid);
        q3[z].waitingt=q3[z].endt-q3[z].startt-q3[z].burstt+1;
        avgwaiting=avgwaiting+q3[z].waitingt;
        totalburst=q3[z].burstt;
    }
    printf("Average waiting time %f \n",avgwaiting/n);
    printf("Turnaround time %f \n",(avgwaiting/n)+totalburst);
    return 0;
}


