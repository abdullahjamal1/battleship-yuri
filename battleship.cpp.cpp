
//   author e-mail :- 2018UCP1712@mnit.ac.
// 

// implement find and probabilityy function nicely and enable human in single player /.........;.....

// BUGS BELOW
// avoid multiple hits in same spot // i think solved
// some unknown bugs still exist in single-player

//// ensure a good random function is implemented // not-essential
//// update probability to hit only even blocks  // not-essential

#include<iostream>

#include<iomanip>

#include<conio.h>   // only for intel

#include<windows.h>

#include<time.h>

#include<fstream>

#define missed  cout<<"\n SHOT MISSED !!!!!"; Sleep(1000)

#define clear system("CLS")    // for intel

#define wait cout<<"\n Press any key to continue "; Sleep(2000)

//#define wait cout<<"\n press any key to continue"; Sleep(3000)

#define msg_arrangeship(grid,k) clear;  cout<<"\n\n ---------------PLAYER  "<<k<<" ARRANGE SHIPS ------------------";  print_map(grid)


// #define clear system("clear")  // for mac/linux 
// add name for player 2

using namespace std;

int find_hit_probability(int probability_AI[10][10] );
int random_hit(int grid[10][10],int *a,int *b);

int print_map(int [10][10]),chain_fire=0,small_size=0;

int arrange_ship(int [10][10],int k);

char name_1[50],name_2[50];

int p1_turn=0,p2_turn=0,AI_turn=0,choice, target_ship=0,target_locked_x[6],target_locked_y[6],target_size=0,otherShip_x[5],otherShip_y[5],otherShip_size=0;

int grid_p1[10][10]={0},grid_p2[10][10]={0},grid_AI[10][10]={0},probability_AI[10][10]={2};  //  re initialize values if re-game chosen use constructor concept

int grid_hidden_p1[10][10]={0},grid_hidden_p2[10][10]={0},grid_hidden_AI[10][10]={0};

static int block[][6]={  {0,2,3,3,4,5} , {0,2,3,3,4,5} , {0,2,3,3,4,5} };


int initialize_variables(){
	

	chain_fire=0;
	small_size=0;
	p1_turn=0;
	p2_turn=0;
	AI_turn=0;
	target_ship=0;
	target_size=0;
	// otherShip_x[6]={0};
	// otherShip_y[6]={0};
	 otherShip_size=0;
	// target_locked_x[6]={0};
	// target_locked_y[6]={0};	
	
	// initialize player name
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			grid_p1[i][j]=0;
			grid_p2[i][j]=0;
			grid_AI[i][j]=0;
			probability_AI[i][j]=2;
			grid_hidden_p1[i][j]=0;
			grid_hidden_p2[i][j]=0;
			grid_hidden_AI[i][j]=0;
		}
	}
	
	for(int i=0;i<=2;i++){
		block[i][1]=2;
		block[i][2]=3;
		block[i][3]=3;
		block[i][4]=4;
		block[i][5]=5;
	}
	
	
	return 0;
}


// displays the status of the ships on top

char* ship_status(int a, int b){
	
	char* ch= new char[9];
	
	
	if(block[a][b]<=0)
	
		strcpy(ch,"DESTROYED");
		
	else
	
		strcpy(ch,"ACTIVE");
		
		return ch;	
		

}

int curr_small_ship(){
	
	int i;
	for( i=1 ; i<=5 ; i++){
	
	if(block[2][i]!=0){
		
		switch(i){
			case 1: i=2;
			break;
			
			
			case 2: i=3;
			break;
			
			case 3: i=3;
			break;
				
			case 4: i=4;
			break;
				
			case 5:	i=5;
			break;	
			
		}

		return i;
		
	}
}
return 0;
}

int storeLog(int k,int turn){
	
	ofstream fout;
	fout.open("battleshipLog.txt", ios::app);
	if(fout.is_open())
		fout<<"\n Player "<<k<<" won in "<<turn<<" turns .";

	fout.close();
	
	return 0;
	
}

int victory(int k,int grid[10][10], int turn){

	clear;
	cout<<"\n ======================================================================";
	if(k==1 || k==2)
	cout<<"\n ------------- PLAYER "<< k<< " WINS !!!!!! "<<" turn :"<<turn<<"------";
	else
	cout<<"\n ---------------- BOT  WINS !!!!!!!!! "<<" turn :"<<turn<<"---------------------------";
		cout<<"\n  aircraft carrier:"<<ship_status(k-1,5)<<"  battleship:"<<ship_status(k-1,4)<<"  destroyer:"<<ship_status(k-1,3)<<"\n  submarine:"<<ship_status(k-1,2)<<" patrol boat:"<<ship_status(k-1,1);
		
	cout<<" \n\n WINNER's MAP       ";
	print_map(grid);

wait;
Sleep(10000);

getchar();

storeLog(k,turn);




return 0;

}



int chainFireSetOtherShipDetected(int x, int y ){
	
	otherShip_x[otherShip_size]=x;
	
	otherShip_y[otherShip_size]=y;
	
	otherShip_size++;
	
	 return 0;
	 
}



int play( int grid[10][10] , int grid_hidden[10][10] , int k , int * turn ){

// k is player
//  im[plement check condition for wrong coordinates as they r resulting in bugs		
		
	int hit_num , target_flag=1 , store=0 ;
	int a,b;
	bool chainFireActive_DiffTarget=0;

	char hit_L;

	if(*turn<100){
	

		extra_shot:

		clear;
		
	//	cout<<"\n ==============================================================================";
		cout<<"\n  --------------------- PLAYER "<<k<<" TURN "<<*turn<<" -----------------------";
		cout<<"\n  aircraft carrier:"<<ship_status(k-1,5)<<"  battleship:"<<ship_status(k-1,4)<<"  destroyer:"<<ship_status(k-1,3)<<"\n  submarine:"<<ship_status(k-1,2)<<" patrol boat:"<<ship_status(k-1,1);
	//	cout<<"\n chain_fire="<<chain_fire<<" small_size= "<<small_size<<" target_size="<<target_size<<std::flush;
		
		
		
		print_map(grid_hidden);
	//	print_map(probability_AI);
		Sleep(2000);

		// execute below if statement only for human players
		
		if(k!=3){
			
				cout<<"\n enter coordinate to strike \n";
				cin>>hit_L>>hit_num;	
		
				}							// eg:: alphabet  1-10
		
		// executes below else statement for AI
		
		else{
		//	wait;

			a=0;
			b=0;

				
			if(!chainFireActive_DiffTarget  ) {
			
				if( chain_fire == 0 && otherShip_size >0 ){
					
				//	skip =1;
					chain_fire=1;
					
						chain_fire=1;
						
						 target_ship=grid[ otherShip_x[otherShip_size-1] ][ otherShip_y[otherShip_size-1] ];
						
						target_size=target_size+1;
						
						target_locked_x[target_size]=otherShip_x[otherShip_size-1];
						target_locked_y[target_size]=otherShip_y[otherShip_size-1];
					
						store=curr_small_ship();
						
						if( target_size >= store )
						
						small_size++;
					
						otherShip_size--;
					
	
					/*
					
					for(;otherShip_size>0;--otherShip_size){
						
						
						// just increasing probability 
						probability_AI[otherShip_x[otherShip_size-1]][otherShip_y[otherShip_size-1]]++;
						probability_AI[otherShip_x[otherShip_size-1]][otherShip_y[otherShip_size-1]]++;
						probability_AI[otherShip_x[otherShip_size-1]][otherShip_y[otherShip_size-1]]++;
						probability_AI[otherShip_x[otherShip_size-1]][otherShip_y[otherShip_size-1]]++;
						probability_AI[otherShip_x[otherShip_size-1]][otherShip_y[otherShip_size-1]]++;
						
					}
					
					*/
					// retrieving other ship
					
				}

			
				find_hit_probability( probability_AI);
				
				chainFireActive_DiffTarget=0;

			}
			
			// random_hit randomly returns a coordinate of highest density 
			
	   		random_hit(probability_AI,&a,&b);
	   		
	   		// assigning the coordinate to hit_L and hit_num
	   		
	   		hit_L='a'+a;                              // because later we subtract '1'
			hit_num=b+1;
			
			
		}
		
		
		

		if( ( grid[ hit_L % 'a' ][ hit_num - 1 ] ) != 0 ){
			
			
			// while the ship is not fully destroyed keep chain fire probability mode on 
			
		
			
			if(k==3)
				probability_AI[ hit_L % 'a' ][ hit_num -1 ]=1;
			
			
			grid_hidden[ hit_L % 'a' ][ hit_num - 1 ] = 1;                 // grid_hidden is the grid that is displayed as ouput on screen
			
			block[k-1][ grid[ hit_L % 'a' ][ hit_num - 1 ] ]--;			// keeps track of ships life
			
			
			
			// if all sank declare victory
			
			if(block[k-1][5]+block[k-1][4]+block[k-1][3]+block[k-1][2]+block[k-1][1]==0)
			
					return 1;

			
			// execute below if-condition only if AI's turn
			
			if(k==3){
			
			
			// execute below if condition only if AI hits opponents ship
			
				if(block[k-1][ grid[ hit_L % 'a' ][ hit_num - 1 ] ]!=0){ 
				
					// chain_fire is set means AI changed strategy from random to chain fire .
					// execute below   :- if statement only when AI is on chain fire on ship A and hits ship B 
					
					if(chain_fire==1 && target_ship!=grid[ hit_L % 'a' ][ hit_num - 1 ] ){
						
						target_flag=0;
						
						chainFireActive_DiffTarget = 1 ;
						
						chainFireSetOtherShipDetected( hit_L % 'a' , hit_num - 1 );
						
						
						// include vect.pushback(coordinate) 
						
					}
					
					
					
					if(target_flag){
						
						chain_fire=1;
						
						 target_ship=grid[ hit_L % 'a' ][ hit_num - 1 ];
						
						target_size=target_size+1;
						
						target_locked_x[target_size]=a;
						target_locked_y[target_size]=b;
					
						store=curr_small_ship();
						
						if( target_size >= store )
						
						small_size++;
					}
					
					
					
				
					target_flag=1;

					
					
				}
			
			// execute below else statement only if AI sinks the opponents ship
			
			else{
				
				small_size= 0;
			
			
				chain_fire=0;
				target_size=0;
				
					for(int e=1;e<=5;e++){
						
						target_locked_x[e]=0;
						target_locked_y[e]=0;
						
					}
				
			}
			
			
			
		}
			
			
			
			goto extra_shot;    // if hit , get extra shot

		}
		
		// executes else part if shot is missed 
		else{
			
			if(k==3)
				probability_AI[ hit_L % 'a' ][ hit_num -1 ]=0;
				
			
			 grid_hidden[ hit_L % 'a' ][ hit_num - 1 ] = 9;	  //  9 indicates shot missed
			 
			 if(k!=3){
		
			 missed;
			}
		
			 //return 0;
	
		}
	}
		clear;
		cout<<"\n  --------------------- PLAYER "<<k<<" TURN "<<*turn<<" -----------------------";
		cout<<"\n  aircraft carrier:"<<ship_status(k-1,5)<<"  battleship:"<<ship_status(k-1,4)<<"  destroyer:"<<ship_status(k-1,3)<<"\n  submarine:"<<ship_status(k-1,2)<<" patrol boat:"<<ship_status(k-1,1);
		print_map(grid_hidden);
		Sleep(1500);
	
	return 0;

}





int find(int a,int b, int horiz, int size){   // inc small ship size if not hit
	
	int i,set=0;
	
	if(horiz){
	for(i=1;i<=target_size;i++){
		
		 if( target_locked_x[i]!=a){
		 	return 0;
		 }
		 if( target_locked_y[i]>=b && target_locked_y[i]<=b+size ){
		 	
		 	set++;
		 }
		// else set=0;
}
}

else{
	for(i=1;i<=target_size;i++){
		
		
		 if( target_locked_y[i]!=b){
		 	return 0;
		 }
		 if( target_locked_x[i]>=a && (target_locked_x[i]<=a+size )){
		 	
		 	set++;
		 }
	//	 else set=0;
	}
	
}

if(set==target_size){
return 1;
}

return 0;
}



int random(int min,int max){
	
	srand(time(0));
	
	return (min + rand() % ( ( max+1 ) - min ));
}


int initialize(int grid[10][10]){
	
	for(int k=1;k<=5;k++){
		
		target_locked_x[k]=0;
		target_locked_y[k]=0;
		
	}
	
	for(int i=0;i<10;i++){
		
		for(int j=0;j<10;j++){
			
			grid[i][j]=0;
		}
	}
	return 0;
}



int arrange_ship_rand(int grid[10][10]){      // lower its complexity   // implement constructor destructor
	
	int size;
	
	initialize(grid);

	
	for(size=5;size>0;size--){
	// put condition for overlap check !!!!!!!!!!!!!!!!!!!!!
	
	int a,b,i,num;
	
	num=size;
	if(size==1 || size==2)
	num++;
	
	
//	jmp1:
	
	if(random(0,1)){               // horizontal arrangement trigger
	
	jmp1:
	
	a = random(0,9);
	b = random(0,10-num);
	
		for(i=0;i<num;i++){
			
			if(grid[a][b+i]!=0)
			
			goto jmp1;
			
		}
		
		for(i=0;i<num;i++){
			
				grid[a][b+i]=size;	    //  horizontal arrangement by random
		}
		
	}



	else{                             		// vertical arrangement trigger  
	
		jmp2:      
		
		b = random(0,9);
		a = random(0,10-num);
		
		for(i=0;i<num;i++){
			
			if(grid[a+i][b]!=0)
			
			goto jmp2;
			
		}
		
		for(i=0;i<num;i++){
		
				grid[a+i][b]=size;	     //  vertical arrangement by random
			
		}
		
		
	}
}

	clear;
	
	print_map(grid);
	
	Sleep(1000);
	
	return 0;
	
}


int random_hit(int grid[10][10],int *a ,int *b){
	
	int ar_i[10]={0},ar_j[10]={0},x=0,shoot_counter=2;
	
	for(int i=0 ; i<10 ;i++){
		
			for(int j=0 ; j<10 ; j++){
					
				if(grid[i][j]>shoot_counter){
					
				shoot_counter=grid[i][j];
				}
		
			}
	}
	
		for(int i=0 ; i<10 ;i++){
			
			for(int j=0 ; j<10 ; j++){
				
					if(grid[i][j]==shoot_counter){
						
			//			if(chain_fire==1){
					ar_i[x]=i;
					ar_j[x]=j;
					x++;
			//	}
				
				
		
				}
		
			}
	}
	x=random(0,x-1);
	
	*a=ar_i[x];
	*b=ar_j[x];
	
	return 0;     //  x and y is the number of high probability spots
}

// grid_filter checks if a ship can be found in a filter

int grid_filter(int grid[10][10],int i, int j , int curr_big_ship, int horiz){
	
	int k;
	
	if(horiz){
	
	for(k=0;k<curr_big_ship;k++){
		
		if(grid[i][j+k]==0)
		return 0;
		
		if(!chain_fire){
			
		if(grid[i][j+k]==1)
		return 0;	
		}
	}
	
}

	else{
	
	
	for(k=0;k<curr_big_ship;k++){	
	
		if(grid[i+k][j]==0)
		return 0;
		
		if(!chain_fire){
			
		if(grid[i+k][j]==1)
		return 0;	
		
		}
	}
}

	return 1;
}


int find_hit_probability(int grid[ 10 ][ 10 ] ){
	
	// add chain fire mechanism and update probability accordingly
	// trigger guess fire if a shot is hit , also update probability with this calling function
	
	int i,j,k,a=0,b=0;
	int curr_big_ship ;


// below initializing to zero 


	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			
			if(grid[i][j]>1)
			grid[i][j]=2;
		}
	}

// below for loop determines the biggest alive ship

	if(chain_fire){
		
		curr_big_ship=curr_small_ship()+small_size;     //   when chain_fire is enabled we will reduce filter to smallest ship
	}


	else{


	// below for loops finds the current biggest alive ship of opponent
		
		for( i=5 ; i>=1 ; i--){
			
			if(block[2][i]!=0){
				
					switch(i){
			case 1: i=2;
			break;
			
			
			case 2: i=3;
			break;
			
			case 3: i=3;
			break;
				
			case 4: i=4;
			break;
				
			case 5:	i=5;
			break;	
			
		}		
				curr_big_ship=i;
				
				break;
				
			}
		}
			

	}
	
	
	// horizontal probability update
	
	
	for(i=0;i<10;i++){
		
		for(j=0;j<=10-curr_big_ship;j++){
			
			if(chain_fire){
				
				a=grid_filter(grid,i,j,curr_big_ship,1);
				
				b= find( i , j ,1,curr_big_ship );
				
				if(a && b) {
					
				}
				else continue;
				
			}
			
			else{
	
				if( !grid_filter(grid,i,j,curr_big_ship,1) ){
				continue;	
				}
			}
		
		  
	//	 if(flag){
		  	
			  for(k=0;k<curr_big_ship;k++){
			  
			  		if(chain_fire){
			  		
					 if(grid[i][j+k]!=0 && grid[i][j+k]!=1){
					 
					 
			  		++grid[i][j+k]; 	
			  		++grid[i][j+k];
			  		++grid[i][j+k]; 	
			  		++grid[i][j+k];
			  		++grid[i][j+k]; 	
			  		
			  			       }                         /// debug this point
					  }
					  
					else{
					  
			  		if(grid[i][j+k]!=0 && grid[i][j+k]!=1)
			  		
			  		++grid[i][j+k];
			  		
			  	}
			  }
		  
	//	}
	
	
		
	}
}


	// vertical probability update
	
		for(i=0;i<=10-curr_big_ship;i++){
			
		for(j=0;j<10;j++){

		
				if(chain_fire){
					
					a=grid_filter(grid,i,j,curr_big_ship,0);
					b= find( i , j, 0, curr_big_ship ); 
					
					if(a && b){
				
					}
					else continue;
					
				}
			
				else{
					
					if(!grid_filter(grid,i,j,curr_big_ship,0)){
						continue;
					
					}
				}		
		  
	//	  if(flag){
		  	
			  for(k=0 ;k<curr_big_ship;k++){
			  	
			  	if(chain_fire){
			  		
			  		if(grid[i+k][j]!=0 && grid[i+k][j]!=1){
					  
			 		++grid[i+k][j]; 	
			  		++grid[i+k][j]; 
			  		++grid[i+k][j]; 	
			  		++grid[i+k][j]; 
			  		++grid[i+k][j];  
			
			  	}
			  		
				}
				
				else{
				  
			  		if(grid[i+k][j]!=0 && grid[i+k][j]!=1)
			  		
			  			++grid[i+k][j];
			  	}
			  	
			  }
	
	//	}
		

			
			
		}
	}


	return 0;
	
}


int single_player(int k=1){         // reveal ur ships for urself in single player AI won't see your ships


	clear;

	print_map(grid_p1);
	msg_arrangeship(grid_p1,1);
//	getchar();
	arrange_ship(grid_p1,1);
//	wait;

	arrange_ship_rand(grid_AI);

	clear;
	print_map(grid_p1);

	for( p1_turn=1 , AI_turn=1 ; p1_turn<100 , AI_turn<100 ; p1_turn++ , AI_turn++ ){       
		
		
		
		if(play(grid_AI , grid_hidden_AI , 1 , &p1_turn )){   // player1 (p1) targets in opponents grid
			
			victory( 1 , grid_p1 , p1_turn );
			break;
		}
	wait;

		
	/*	else*/ if( play(grid_p1 , grid_hidden_p1 , 3 , &AI_turn ) ){  // bot targets in player1's grid
			
			victory( 3 , grid_AI , AI_turn );
			break;
		}
		


}
	return 0;
}


int multi_player(){
	
	clear;    //  for creating new blank screen
	
	/*
	cout<<"\n enter Player 1 name \n";
	cin>>name_1;
	cout<<"\n\n enter Player 2 name \n";
	cin>>name_2;
	*/
	getchar();
	
	clear;
	
	cout<<"\n PLAYER 1 \n"<<name_1;
	print_map(grid_p1);	
	msg_arrangeship(grid_p1,1);
	getchar();	
	arrange_ship(grid_p1,1);

	clear;
	
	cout<<"\n PLAYER 2 \n"<<name_2;
	print_map( grid_p2 );
	msg_arrangeship( grid_p2 , 2 );
	getchar();
	arrange_ship( grid_p2 , 2 );
	
	
	clear;

	for( p1_turn=1 , p2_turn=1 ; p1_turn<100 , p2_turn<100 ; p1_turn++ , p2_turn++ ){         // change number of turns for different players
		
	if( play( grid_p2 , grid_hidden_p2 , 1 , &p1_turn )){
		
		victory( 1 , grid_p1 , p1_turn );
		
		return 1;
		
		
	}
	
	Sleep( 1000 );
	
	if( play( grid_p1 , grid_hidden_p1 , 2 , &p2_turn ) ){
		
		victory( 2 , grid_p2 , p2_turn );
		
		return 1;
		
	}
	
	Sleep(1000);

}
return 0;	
	
}


int print_map(int grid[10][10]){         // check for memory buffer problem while printing

	int a=0,b=0;
	
	char ch='a';
	
	cout<<endl;
	cout<<"\n   1 2 3 4 5 6 7 8 9 10 \n"<<std::flush;

	for(a=0;a<10;a++){
		
		cout<<ch++<<" ";		

		for(b=0;b<10;b++){
		
	//	if(grid[a][b]==0)
	//	SetConsoleTextAttribute(color,12);
	// above command was for adding colour ignore it
	
	if(grid[a][b]==0)
//	cout<<" "<<" "<<" ";
cout<<"  ";
	else if(grid[a][b]==9)
//	cout<<" 0 ";
	cout<<" 0";
	else
//		cout<<" "<<1<<" ";
//	cout<<" 1";
	cout<<" "<<grid[a][b]<<std::flush;

		}

	cout<<"\n";

}
	return 0;
}


int input_coordinate(int grid[10][10],int i){

	int k=0,num=0,size=i;
	char ship[1];

	if(i==2 || i==1)
	size=i+1;
	
	for(k=0;k<size;k++){

			cin>>ship[0]>>num;

			grid[ship[0]%'a'][num-1]=i;
	}

	return 0;
}


int arrange_ship(int grid[10][10],int k){     // add code for overlap

int choice =0;


re_arrange:
msg_arrangeship(grid,k);

cout<<"\n enter your choice \n";
cout<<" 1. auto \n 2. manual \n";
cin>>choice;

if(choice==1)
	arrange_ship_rand(grid);

	else{
		msg_arrangeship(grid,k);
		cout<<"\n enter coordinate of aircraft carrier ";
		input_coordinate(grid,5);
		clear;
		
		msg_arrangeship(grid,k);
		cout<<"\n enter coordinate of battleship ";
		input_coordinate(grid,4);
		clear;
		
		msg_arrangeship(grid,k);
		cout<<"\n enter coordinate ofdestroyer ";
		input_coordinate(grid,3);
		clear;
		
		msg_arrangeship(grid,k);
		cout<<"\n enter coordinate of submarine ";
		input_coordinate(grid,2);
		clear;
		
		msg_arrangeship(grid,k);
		cout<<"\n enter coordinate of patrol boat ";
		input_coordinate(grid,1);
		clear;
		
	}
	msg_arrangeship(grid,k);
	cout<<"\n enter your choice ";
	cout<<"\n 1.confirm \n 2.re-arrange ship \n";
	cin>>choice;
	
	if(choice==2){
		goto re_arrange;
	}


return 0;
}

int statistics(){
	clear;
	return 0;
}

int multi_player_online(){    // requires team-work

	cout<<"coming soon ..";
	wait;
	clear;
	return 0;
}


int settings(){
	clear;
	int choice;
	
	cout<<"SETTINGS";
	
	cout<<"\n 1. colour change ";
	cout<<"\n 2. music  setting ";
	cout<<"\n 3. missing ";
	cout<<"\n 4. game modes ";      // like classic , russian 
	cin>> choice ;
	
	getchar();
	
	return 0;
	
}

int main(){

wait;

	int choice;	


	jmp:
		
		
	//	initialize all values here 
	
	initialize_variables();
		
		
		clear;
	



	cout<<"\n welcome";
	
	cout<<"\n ============================================================";

	cout<<"\n                BATTLESHIP CLASSIC BOARD GAME                ";

	cout<<"\n                   1.  Single player                  ";
	cout<<"\n                   2.  Multiplayer (offline)          ";
	cout<<"\n                   3.  Multiplayer (Online)           ";
	cout<<"\n                   4.  Statistics                     ";
	cout<<"\n                   5.  settings                       ";
	cout<<"\n                   6.  exit                           ";

	cout<<"\n ============================================================  \n\n";

	cin>>choice;

	clear;

	switch(choice){

		case 1:  single_player(1);
				goto jmp;
		case 2:  multi_player();
				goto jmp;
		case 3:  multi_player_online();
				goto jmp;
		case 4:  statistics();
				goto jmp;
		case 5:  settings();
				goto jmp;
		case 6: return 0;				
					break;
		default:  cout<<"choice not found !!! enter again \n ";
	goto jmp;				

	}
	return 0;
}
