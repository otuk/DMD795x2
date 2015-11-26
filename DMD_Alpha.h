#ifndef  DMD_ALPHA_H
#define DMD_ALPHA_H

typedef struct{
  byte r; //rows 1...8
  byte c; //colums 1...8  - pair_s{1,1} is the top left corner led
} pair_s;

const pair_s l11=pair_s{1,1};const pair_s l12=pair_s{1,2};const pair_s l13=pair_s{1,3};
const pair_s l14=pair_s{1,4};const pair_s l15=pair_s{1,5};const pair_s l16=pair_s{1,6};
const pair_s l21=pair_s{2,1};const pair_s l22=pair_s{2,2};const pair_s l23=pair_s{2,3};
const pair_s l24=pair_s{2,4};const pair_s l25=pair_s{2,5};const pair_s l26=pair_s{2,6};
const pair_s l31=pair_s{3,1};const pair_s l32=pair_s{3,2};const pair_s l33=pair_s{3,3};
const pair_s l34=pair_s{3,4};const pair_s l35=pair_s{3,5};const pair_s l36=pair_s{3,6};
const pair_s l41=pair_s{4,1};const pair_s l42=pair_s{4,2};const pair_s l43=pair_s{4,3};
const pair_s l44=pair_s{4,4};const pair_s l45=pair_s{4,5};const pair_s l46=pair_s{4,6};
const pair_s l51=pair_s{5,1};const pair_s l52=pair_s{5,2};const pair_s l53=pair_s{5,3};
const pair_s l54=pair_s{5,4};const pair_s l55=pair_s{5,5};const pair_s l56=pair_s{5,6};
const pair_s l61=pair_s{6,1};const pair_s l62=pair_s{6,2};const pair_s l63=pair_s{6,3};
const pair_s l64=pair_s{6,4};const pair_s l65=pair_s{6,5};const pair_s l66=pair_s{6,6};

const pair_s lend=pair_s{0xFF,0xFF};

////// alphabet //////////
const pair_s A[] ={
      l13,l14,
  l22,        l25,
  l32,l33,l34,l35,  
  l42,        l45,
  l52,        l55,  
  lend
};

const pair_s B[] ={
  l12,l13,l14,
  l22,        l25,
  l32,l33,l34,
  l42,        l45,
  l52,l53,l54,        
  lend  
};

const pair_s C[] ={
      l13,l14,
  l22,
  l32,
  l42,
      l53,l54, 
  lend  
};

const pair_s D[] ={
  l12,l13,l14,
  l22,        l25,
  l32,        l35,
  l42,        l45,
  l52,l53,l54, 
  lend  
};

const pair_s E[] ={
  l12,l13,l14,
  l22,                    
  l32,l33,l34,
  l42,                   
  l52,l53,l54,                 
  lend  
};

const pair_s F[] ={
  l12,l13,l14,
  l22,                    
  l32,l33,l34,
  l42,                   
  l52,                     
  lend  
};

const pair_s G[] ={
      l13,l14,
  l22,                    
  l32,    l34,l35,
  l42,        l45,
      l53,l54, 
  lend  
};

const pair_s H[] ={
  l12,    l14,
  l22,    l24,
  l32,l33,l34,
  l42,    l44,
  l52,    l54, 
  lend  
};

const pair_s I[] ={
            l13,l14,l15,
                l24,
                l34, 
                l44,         
            l53,l54,l55,          
  lend  
};

const pair_s J[] ={
            l13,l14,l15,
                l24,
                l34, 
        l42,    l44,         
            l53,          

  lend  
};

const pair_s K[] ={
  l12,        l15,
  l22,    l24,
  l32,l33,
  l42,    l44,           
  l52,        l55,           
  lend  
};

const pair_s L[] ={
  l12,
  l22,                    
  l32,
  l42,                   
  l52,l53,l54,                    
  lend  
};

const pair_s M[] ={
  l12,            l16,
  l22,l23,    l25,l26,
  l32,    l34,    l36,
  l42,            l46,
  l52,            l56, 
  lend  
};

const pair_s N[] ={
  l12,          l15,
  l22,l23,      l25,
  l32,     l34, l35,
  l42,     l44, l45,
  l52,          l55, 
  lend  
};

const pair_s O[] ={
      l13,l14,
  l22,        l25,
  l32,        l35,
  l42,        l45,
      l53,l54, 
  lend  
};

const pair_s P[] ={
  l12,l13,l14,
  l22,        l25,
  l32,l33,l34,
  l42,                    
  l52,                    
  lend  
};

const pair_s Q[] ={
      l13,l14,
  l22,        l25,
  l32,    l34,l35,
  l42,    l44,
      l53,    l55,
  lend  
};

const pair_s R[] ={
  l12,l13,l14,
  l22,        l25,
  l32,l33,l34,
  l42,    l44,                     
  l52,        l55,           
  lend  
};

const pair_s S[] ={
      l13,l14,
  l22,        
      l33,l34,
              l45,                     
  l52,l53,l54,           
  lend  
};

const pair_s T[] ={
       l13,l14,l15,
           l24,
           l34, 
           l44,         
           l54,          
  lend  
};

const pair_s U[] ={
  l12,        l15,
  l22,        l25,
  l32,        l35,
  l42,        l45,
      l53,l54,
  lend  
};

const pair_s V[] ={
  l12,          l16,
  l22,          l26,
     l33,   l35,
     l43,   l45,
         l54, 
  lend  
};

const pair_s W[] ={
  l12,          l16,
  l22,          l26,
  l32,   l34,   l36,
  l42,   l44,   l46,
     l53,   l55,
  lend  
};


const pair_s X[] ={
  l12,            l16,
      l23,    l25,
          l34,      
      l43,    l45, 
  l52,            l56,
  lend  
};

const pair_s Y[] ={
  l12,        l15,
      l23,    l25,
          l34,      
      l43,
  l52,              
  lend  
};

const pair_s Z[] ={
  l12,l13,l14,l15,
              l25,            
          l34,    
      l43,        
  l52,l53,l54,l55,        
  lend  
};
/////// punctuation ///////////////

const pair_s NOTYET[] ={

          
          l33,l34,
          l43,l44,
          l53,l54,
            
  lend  
};

const pair_s space[] ={
  lend  
};

const pair_s exclamation[] ={
                      l14,
                      l24,
                      l34, 
                      l44,         
                                
                      l64,
  lend  
};


const pair_s quote[] ={
  l12,   l14,
  l22,   l24,  
  lend  
};

const pair_s* pound = NOTYET;

const pair_s* dollar = NOTYET;

const pair_s* percentage = NOTYET;

const pair_s* ampersend = NOTYET;

const pair_s* singlequote = NOTYET;

const pair_s* openparan = NOTYET;

const pair_s* closeparan = NOTYET;

const pair_s* star = NOTYET;

const pair_s* plus = NOTYET;

const pair_s comma[] = {
                     
                     
                      
              l45,                
              l55,                         
           l64,
  lend  
}; 

const pair_s* minus= NOTYET;

const pair_s period[] = {
                     
                     
                      
                           
       l53,l54,                         
       l63,l64,
  lend  
};

const pair_s* slash = NOTYET;
//////// digits //////////////////
const pair_s zero[] = {
  l22,l23,l24,
  l32,    l34,
  l42,    l44,
  l52,    l54,
  l62,l63,l64,  
  lend
};

const pair_s one[] = {
          l24,
          l34,
          l44,
          l54,
          l64,  
  lend
};

const pair_s two[] = {
  l22,l23,l24,
          l34,
  l42,l43,l44,
  l52,     
  l62,l63,l64,  
  lend
};


const pair_s three[] = {
  l22,l23,l24,
            l34,
  l42,l43,l44,
            l54,
  l62,l63,l64,  
  lend
};


const pair_s four[] = {
  l22,    l24,
  l32,    l34,
  l42,l43,l44,
          l54,
          l64,  
  lend
};

const pair_s five[] = {
  l22,l23,l24,
  l32,    
  l42,l43,l44,
          l54,
  l62,l63,l64,  
  lend
};

const pair_s six[] = {
  l22,
  l32,    
  l42,l43,l44,
  l52,    l54,
  l62,l63,l64,  
  lend
};

const pair_s seven[] = {
  l22,l23,l24,
          l34,
          l44,
          l54,
          l64,  
  lend
};;

const pair_s eight[] = {
  l22,l23,l24,
  l32,    l34,
  l42,l43,l44,
  l52,    l54,
  l62,l63,l64,  
  lend
};

const pair_s nine[] = {
  l22,l23,l24,
  l32,    l34,
  l42,l43,l44,
          l54,
          l64,  
  lend
};

const pair_s* colon = NOTYET;

const pair_s* semicolon = NOTYET;

const pair_s* lessthan = NOTYET;

const pair_s* equal = NOTYET;

const pair_s* greaterthan = NOTYET;

const pair_s* question = NOTYET;

const pair_s* at = NOTYET;

// !"#$%&'()*+,-./0123456789:;<=>?@
//#define PUNC_SIZE 33
//const pair_s* PUNC[PUNC_SIZE]={space, exclamation, quote, pound, dollar, percentage,
//                               ampersend, singlequote, openparan, closeparan, star, plus,
//                               comma, minus,period,slash, zero, one, two, three, four, 
//                               five, six, seven, eight, nine, colon, semicolon, lessthan, 
//                               equal, greaterthan, question, at };
//const pair_s* ALPHA[ALPHA_SIZE]={A, B, C, D, E, F, G, H, I, J, 
//                       K, L, M, N, O, P, Q, R, S, T, 
//                       U, V, W, X, Y, Z };

#define ALPHA_SIZE 59
const pair_s* ALPHA[ALPHA_SIZE]= {space, exclamation, quote, pound, dollar, percentage,
                               ampersend, singlequote, openparan, closeparan, star, plus,
                               comma, minus,period,slash, zero, one, two, three, four, 
                               five, six, seven, eight, nine, colon, semicolon, lessthan, 
                               equal, greaterthan, question, at,
                               A, B, C, D, E, F, G, H, I, J, 
                               K, L, M, N, O, P, Q, R, S, T, 
                               U, V, W, X, Y, Z };                    

#endif
