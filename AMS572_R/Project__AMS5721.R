
install.packages('stargazer')
install.packages("huxtable")
install.packages("car")
install.packages('tidyquant')
install.packages("jtools")
install.packages("ggstance")
install.packages('tidyverse')
library('stargazer')
library('tidyquant')
library(tidyverse)
install.packages("ggplot2")

#Cleaning Data
data <- Portfolios_Formed_on_ME
fama <- F_F_Research_Data_Factors
fama <- fama[-c(718:1119),]
data <- data[-c(718:3573),]
data <- data[-c(2:9)]

###function fama regression
test<-function(fama,ri){
  newdata<-cbind(fama,ri)
  colnames(newdata)<- c("Date","Mkt-rf","SMB","HML","RF","Ri")
  return(lm((newdata$Ri-newdata$RF) ~ newdata$'Mkt-rf' +newdata$SMB + newdata$HML))
}
###function compare before and after data
fama.compare<-function(fama1,fama2,ri){
  xtable<-cbind(fama1,fama2,ri)
  colnames(xtable)<- c('Date1','MktRf1','SMB1','HML1','RF1','Date2','MktRf2','SMB2','HML2','RF2','ri')
  lm.compare<-lm((xtable$ri-xtable$RF1-xtable$RF2)~xtable$MktRf1+xtable$SMB1+xtable$HML1+xtable$MktRf2+xtable$SMB2+xtable$HML2)
  return(lm.compare)
}

### function generate NA in data frame
gene.NA<-function(data){
  fama.NA<-data
  n<-dim(fama.NA)[1]
  i=1
  while (i <= dim(fama.NA)[2]) {
    random1<-sample(1:n,ceiling(0.2*n),replace = F)
    fama.NA[random1, i]<-rep(NA,ceiling(0.2*n))
    i=i+1
  }
  return(fama.NA)
}

###data used for test
colnames(fama)[1]<-c('Date')
fama.after<-fama
fama.after[which(fama.after$Date<199001),]<-0
fama.before<-fama
fama.before[which(fama.before$Date>=199001),]<-0
fama.NA<-gene.NA(fama)
data.NA<-gene.NA(data)

#Lo.10
lm.total.Lo.10<-test(fama,data[,2])
lm.NA.Lo.10<-test(fama.NA,data.NA[,2])
lm.compare.Lo.10<-fama.compare(fama.before,fama.after,data[,2])
#Plots
qqnorm(lm.total.Lo.10$residuals, main = "Normal Q-Q plot for Residuals Lo10")
qqline(lm.total.Lo.10$residuals)
plot_coefs(lm.total.Lo.10,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.Lo.10,lm.NA.Lo.10,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("Lo10","Lo10 MissingValues"))
summary(lm.compare.X1.Dec)

#X2.Dec
lm.total.X2.Dec<-test(fama,data[,3])
lm.NA.X2.Dec<-test(fama.NA,data.NA[,3])
lm.compare.X2.Dec<-fama.compare(fama.before,fama.after,data[,3])
#Plots
qqnorm(lm.total.X2.Dec$residuals, main = "Normal Q-Q plot for Residuals X2.Dec")
qqline(lm.total.X2.Dec$residuals)
plot_coefs(lm.total.X2.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X2.Dec,lm.NA.X2.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X2.Dec","X2.Dec MissingValues"))
summary(lm.compare.X2.Dec)


#X3.Dec
lm.compare.X3.Dec<-fama.compare(fama.before,fama.after,data[,4])
lm.total.X3.Dec<-test(fama,data[,4])
lm.NA.X3.Dec<-test(fama.NA,data.NA[,4])
#Plots
qqnorm(lm.total.X3.Dec$residuals, main = "Normal Q-Q plot for Residuals X3.Dec" )
qqline(lm.total.X3.Dec$residuals)
plot_coefs(lm.total.X3.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X3.Dec,lm.NA.X3.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X3.Dec","X3.Dec MissingValues"))
summary(lm.compare.X3.Dec)

#X4.Dec
lm.total.X4.Dec<-test(fama,data[,5])
lm.NA.X4.Dec<-test(fama.NA,data.NA[,5])
lm.compare.X4.Dec<-fama.compare(fama.before,fama.after,data[,5])
#Plots
qqnorm(lm.total.X4.Dec$residuals, main = "Normal Q-Q plot for Residuals X4.Dec" )
qqline(lm.total.X4.Dec$residuals)
plot_coefs(lm.total.X4.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X4.Dec,lm.NA.X4.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X4.Dec","X4.Dec MissingValues"))
summary(lm.compare.X4.Dec)


#X5.Dec
lm.total.X5.Dec<-test(fama,data[,6])
lm.NA.X5.Dec<-test(fama.NA,data.NA[,6])
lm.compare.X5.Dec<-fama.compare(fama.before,fama.after,data[,6])
#Plots
qqnorm(lm.total.X5.Dec$residuals, main = "Normal Q-Q plot for Residuals X5.Dec" )
qqline(lm.total.X5.Dec$residuals)
plot_coefs(lm.total.X5.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X5.Dec,lm.NA.X5.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X5.Dec","X5.Dec MissingValues"))
summary(lm.compare.X5.Dec)

#X6.Dec
lm.total.X6.Dec<-test(fama,data[,7])
lm.NA.X6.Dec<-test(fama.NA,data.NA[,7])
lm.compare.X6.Dec<-fama.compare(fama.before,fama.after,data[,7])
#Plots
qqnorm(lm.total.X6.Dec$residuals, main = "Normal Q-Q plot for Residuals X6.Dec" )
qqline(lm.total.X6.Dec$residuals)
plot_coefs(lm.total.X6.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X6.Dec,lm.NA.X6.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X6.Dec","X6.Dec MissingValues"))
summary(lm.compare.X6.Dec)


#X7.Dec
lm.total.X7.Dec<-test(fama,data[,8])
lm.NA.X7.Dec<-test(fama.NA,data.NA[,8])
lm.compare.X7.Dec<-fama.compare(fama.before,fama.after,data[,8])
#Plots
qqnorm(lm.total.X7.Dec$residuals, main = "Normal Q-Q plot for Residuals X7.Dec" )
qqline(lm.total.X7.Dec$residuals)
plot_coefs(lm.total.X7.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X7.Dec,lm.NA.X7.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X7.Dec","X7.Dec MissingValues"))
summary(lm.compare.X7.Dec)

#X8.Dec
lm.total.X8.Dec<-test(fama,data[,9])
lm.NA.X8.Dec<-test(fama.NA,data.Na[,9])
lm.compare.X8.Dec<-fama.compare(fama.before,fama.after,data[,9])
#Plots
qqnorm(lm.total.X8.Dec$residuals, main = "Normal Q-Q plot for Residuals X8.Dec" )
qqline(lm.total.X8.Dec$residuals)
plot_coefs(lm.total.X8.Dec,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.X8.Dec,lm.NA.X8.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X8.Dec","X8.Dec MissingValues"))
summary(lm.compare.X8.Dec)

#X9.Dec
lm.total.X9.Dec<-test(fama,data[,9])
lm.NA.X9.Dec<-test(fama.NA,data[,9])
lm.compare.X9.Dec<-fama.compare(fama.before,fama.after,data[,10])
#Plots
qqnorm(lm.total.X9.Dec$residuals, main = "Normal Q-Q plot for Residuals X6.Dec" )
qqline(lm.total.X9.Dec$residuals)
plot_coefs(lm.total.X9.Dec,ci_level = 0.99,omit.coefs = NULL,legend.title = "Regression Estimates for Lo10")
#Compare Results
export_summs(lm.total.X9.Dec,lm.NA.X9.Dec,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("X9.Dec","X9.Dec MissingValues"))
summary(lm.compare.X9.Dec)

#Hi.10
lm.total.Hi.10<-test(fama,data[,11])
lm.NA.Hi.10<-test(fama.NA,data.NA[,11])
lm.compare.Hi.10<-fama.compare(fama.before,fama.after,data[,11])
#Plots
qqnorm(lm.total.Hi.10$residuals, main = "Normal Q-Q plot for Residuals X6.Dec" )
qqline(lm.total.Hi.10$residuals)
plot_coefs(lm.total.Hi.10,ci_level = 0.99,omit.coefs = NULL)
#Compare Results
export_summs(lm.total.Hi.10,lm.NA.Hi.10c,error_format = "[{conf.low},{conf.high}],{p.value}",ci_level = 0.99,model.names = c("Hi.10","Hi.10 MissingValues"))
summary(lm.compare.Hi.10)