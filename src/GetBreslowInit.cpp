#include <RcppEigen.h>

// [[Rcpp::depends(RcppEigen)]]

//
// [[Rcpp::export]]
Rcpp::List GetBreslowInit(const Eigen::MatrixXd & cdata,
                          const Eigen::VectorXd & vi) {
  
  int k = cdata.rows();
  int a=0,b=0;
  double u=0;
  int i,j;
  Eigen::MatrixXd FH01 = Eigen::MatrixXd::Zero(k, 2);
  Eigen::MatrixXd FH02 = Eigen::MatrixXd::Zero(k, 2);
  
  /* find # events for risk 1*/
  for (j=0;j<k;j++)
  {
    if (cdata(j,1) == 1)
    {
      u = u + vi(j);
      if (j == k-1)
      {
        a++;
        FH01(k-a,0) = cdata(j,0);
        FH01(k-a,1) = u;
        u=0;
      }
      else if (cdata(j+1,0) != cdata(j,0))
      {
        a++;
        FH01(k-a,0) = cdata(j,0);
        FH01(k-a,1) = u;
        u=0;
      }
      else
      {
        for (j=j+1;j<k;j++)
        {
          if (cdata(j,1) == 1)
          {
            u = u + vi(j);
            if (j == k-1)
            {
              a++;
              FH01(k-a,0) = cdata(j,0);
              FH01(k-a,1) = u;
              u=0;
              break;
            }
            else if (cdata(j+1,0) != cdata(j,0))
            {
              a++;
              FH01(k-a,0) = cdata(j,0);
              FH01(k-a,1) = u;
              u=0;
              break;
            }
            else continue;
          }
          else
          {
            if (j == k-1)
            {
              a++;
              FH01(k-a,0) = cdata(j,0);
              FH01(k-a,1) = u;
              u=0;
              break;
            }
            else if (cdata(j+1,0) != cdata(j,0))
            {
              a++;
              FH01(k-a,0) = cdata(j,0);
              FH01(k-a,1) = u;
              u=0;
              break;
            }
            else continue;
          }
        }
      }
      
    }
    else continue;
  }
  
  if(a==0)
  {
    Rprintf("No failure time information for risk 1; Program exits\n");
    return ( -1.0 );
  } 
  
  Eigen::MatrixXd H01 = Eigen::MatrixXd::Zero(a, 3);
  for(i=0;i<3;i++)
  {
    if(i<=1)
    {
      for(j=a;j>0;j--)    H01(a-j,i) = FH01(k-j,i);
    }
    if(i==2)
    {
      for(j=0;j<a;j++)    H01(j,i) = 0.0001;
    }
  }
  
  
  u=0;
  /* find # events for risk 2*/
  for (j=0;j<k;j++)
  {
    if (cdata(j,1) == 2)
    {
      u = u + vi(j);
      if (j == k-1)
      {
        b++;
        FH02(k-b,0) = cdata(j,0);
        FH02(k-b,1) = u;
        u=0;
      }
      else if (cdata(j+1,0) != cdata(j,0))
      {
        b++;
        FH02(k-b,0) = cdata(j,0);
        FH02(k-b,1) = u;
        u=0;
      }
      else
      {
        for (j=j+1;j<k;j++)
        {
          if (cdata(j,1) == 2)
          {
            u = u + vi(j);
            if (j == k-1)
            {
              b++;
              FH02(k-b,0) = cdata(j,0);
              FH02(k-b,1) = u;
              u=0;
              break;
            }
            else if (cdata(j+1,0) != cdata(j,0))
            {
              b++;
              FH02(k-b,0) = cdata(j,0);
              FH02(k-b,1) = u;
              u=0;
              break;
            }
            else continue;
          }
          else
          {
            if (j == k-1)
            {
              b++;
              FH02(k-b,0) = cdata(j,0);
              FH02(k-b,1) = u;
              u=0;
              break;
            }
            else if (cdata(j+1,0) != cdata(j,0))
            {
              b++;
              FH02(k-b,0) = cdata(j,0);
              FH02(k-b,1) = u;
              u=0;
              break;
            }
            else continue;
          }
        }
      }
      
    }
    else continue;
  }
  
  if(b==0)
  {
    Rprintf("No failure time information for risk 2; Program exits\n");
    return ( -1.0 );
  } 
  
  Eigen::MatrixXd H02 = Eigen::MatrixXd::Zero(b, 3);
  for(i=0;i<3;i++)
  {
    if(i<=1)
    {
      for(j=b;j>0;j--)    H02(b-j,i) = FH02(k-j,i);
    }
    if(i==2)
    {
      for(j=0;j<b;j++)    H02(j,i) = 0.0001;
    }
  }
  
  return Rcpp::List::create(Rcpp::Named("H01")=H01,
                            Rcpp::Named("H02")=H02);
  
}