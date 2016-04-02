#include"Sudoku.h"
#include<string>
Sudoku::Sudoku(){
	for(int i=0;i<SudokuSize;i++){
		map[i]=0;
	}
}



/*Sudoku::sudoku(const int init_map[]){
	for(int i;i<SudokuSize;i++){
		map[i]=init_map[i];
	}
}*/

void Sudoku::giveQuestion(){
	int	set_map[81] = {0,2,0,0,0,0,0,0,0,6,1,7,2,5,8,0,4,0,0,4,8,0,9,0,2,0,1,1,7,0,5,0,0,0,9,0,0,0,6,0,0,0,7,0,0,0,9,0,0,0,4,0,6,2,7,0,4,0,8,0,1,2,0,0,6,0,4,7,1,9,3,8,0,0,0,0,0,0,0,7,0};
	for(int i=0;i<SudokuSize;i++)map[i]=set_map[i];
    printout();
}

void Sudoku::readIn(){
	for(int i=0;i<SudokuSize;i++){
		map[i]=0;
	}


	for(int i=0;i<SudokuSize;i++){
		cin>>map[i];
	}
	//printout();
}

void Sudoku::changeNum(int a, int b){
	int i,j =0;
	int change[SudokuSize];
	for(i=0;i<SudokuSize;i++)change[i]=0;
	for(i=0;i<SudokuSize;i++){
		if(map[i]==a){map[i]=b;change[i]=1;}
	}
	for(j=0;j<SudokuSize;j++){
		if(map[j]==b&&change[j]!=1)map[j]=a;
	}
}


void Sudoku::changeRow(int a, int b){
	int i,j,k=0;
	int element = 0;
	int temp1[27];
	for(i=0;i<27;i++)temp1[i]=0;
	i=0;
	for(j=a*27;j<a*27+27;j++){
		element=map[j];
		temp1[i]=element;
		i++;
	}
	for(k=b*27;k<b*27+27;k++){
		element=map[k];
		map[k+(a-b)*27]=element;
	}
	i=0;
	k=0;
	for(k=b*27;k<b*27+27;k++){
		element=temp1[i];
		map[k]=element;
		i++;
	}
}


void Sudoku::printout(){
	for(int m=0;m<SudokuSize;m++){
		cout<<map[m];
		if(m%9!=8)cout<<" ";
		if(m%9==8)cout<<endl;
	}
}



void Sudoku::transpose(){
	int a[9][9];
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			a[i][j]=0;
	int element=0;
	int k=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			element=map[k];
			a[i][j]=element;
			k++;
		}
	}
	for(int i=0;i<9;i++){
		for(int j=i+1;j<9;j++){
			element=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=element;
		}
	}
	k=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			element=a[i][j];
			map[k]=element;
			k++;
		}
	}
}


void Sudoku::changeCol(int a, int b){
	transpose();
	changeRow(a,b);
	transpose();
	//printout();
}



void Sudoku::flip(int n){
	int newmap[SudokuSize];
	for(int i=0;i<SudokuSize;i++)newmap[i]=0;
	switch(n){
	case 0:
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				newmap[i*9+j]=map[(8-i)*9+j];
			}
		}
		for(int i=0;i<SudokuSize;i++)map[i]=newmap[i];
		break;
	case 1:
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				newmap[i*9+j]=map[i*9+(8-j)];
			}
		}
		for(int i=0;i<SudokuSize;i++)map[i]=newmap[i];
		break;
	}
	//printout();
}
		

void Sudoku::rotate(int n){
	int m;
	int newmap[SudokuSize];
	for(int i=0;i<SudokuSize;i++)newmap[i]=0;
	m=(n+4)%4;
	switch(m){
		case 0:break;
		case 1:
			   for(int i=0;i<9;i++)
				for(int j=0;j<9;j++)
				newmap[i*9+j]=map[9*(8-j)+i];
			   for(int i=0;i<SudokuSize;i++)
				   map[i]=newmap[i];
			   break;
		case 2:
			   flip(0);
			   flip(1);
			   break;
		case 3:
			   for(int i=0;i<9;i++)
				for(int j=0;j<9;j++)
				newmap[i*9+j]=map[(8-i)+9*j];
			   for(int i=0;i<SudokuSize;i++)
				 	map[i]=newmap[i];
			   break;
	}

	//printout();
}

						
void Sudoku::transform(){
	srand(time(NULL));
	int q;
	for(int i=0;i<111;i++){
		q=rand()%6;
		switch(q){
			case 0:
				changeNum(rand()%9+1,rand()%9+1);
				break;
			case 1:
				changeRow(rand()%3, rand()%3);
				break;
			case 2:
				changeCol(rand()%3, rand()%3);
				break;
			case 3:
				rotate(rand()%113);
				break;
			case 4:
				flip(rand()%2);
				break;
			case 5:
				transpose();
				break;
		}
	}
	printout();
}

				

/*bool Sudoku::prejudge(){
	//prejudge whether it is more than one solution
	//any two rows or columns in big row/column are 0, return false
	int blankrow[9];
	int blankcol[9];
	for(int i=0;i<9;i++){blankrow[i]=0;blankcol[i]=0;}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(map[i*9+j]!=0)break;
			if(j==8)blankrow[i]=1;
		}
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(map[i+9*j]!=0)break;
			if(j==8)blankcol[i]=1;
		}
	}
	if((blankrow[0]==1&&blankrow[2]==1)||(blankrow[1]==1&&blankrow[2]==1)||(blankrow[0]==1&&blankrow[1]==1))return false;
	else if((blankrow[3]==1&&blankrow[4]==1)||(blankrow[3]==1&&blankrow[5]==1)||(blankrow[4]==1&&blankrow[5]==1))return false;
	else if((blankrow[6]==1&&blankrow[7]==1)||(blankrow[6]==1&&blankrow[8]==1)||(blankrow[7]==1&&blankrow[8]==1))return false;
	else if((blankcol[0]==1&&blankcol[2]==1)||(blankcol[1]==1&&blankcol[2]==1)||(blankcol[0]==1&&blankcol[1]==1))return false;
	else if((blankcol[3]==1&&blankcol[4]==1)||(blankcol[3]==1&&blankcol[5]==1)||(blankcol[4]==1&&blankcol[5]==1))return false;
	else if((blankcol[6]==1&&blankcol[7]==1)||(blankcol[6]==1&&blankcol[8]==1)||(blankcol[7]==1&&blankcol[8]==1))return false;
	
	//for the big row/col, if a big square has two nonzeros,but another squares are zero,then return false
	int blanksquare[9];
	int count = 0;
	for(int i=0;i<9;i++)blanksquare[i]=0;
	for(int m=0;m<3;m++){
		count =0;
		for(int k=0;k<3;k++){
			count=0;
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(map[27*m+3*k+9*i+j]!=0)count++;
				}
			}
			blanksquare[3*m+k]=count;
		}
	}
	int threeSquaNon=0;
	for(int i=0;i<3;i++){
		threeSquaNon=0;
		for(int j=0;j<3;j++)threeSquaNon=threeSquaNon+blanksquare[3*i+j];
		if(threeSquaNon<2||(threeSquaNon==2&&(!(blanksquare[3*i]==1||blanksquare[3*i+1]==1)))){return false;break;}
	}
	for(int i=0;i<3;i++){
		threeSquaNon=0;
		for(int j=0;j<3;j++)threeSquaNon=threeSquaNon+blanksquare[i+3*j];
		if(threeSquaNon<2||(threeSquaNon==2&&(!(blanksquare[i]==1||blanksquare[i+3]==1)))){return false;break;}
	}


	
	//if nonzeros <17,return false
	int nonzero=0;
	for(int i=0;i<9;i++)nonzero=nonzero+blanksquare[i];
	if(nonzero<17)return false;

	//if two kinds of number are missing, return false
	//numtype[0~8]=1~9
	int numtype[9];
	int catchnum = 0;
	int numtypeSum = 0;
	for(int i=0;i<9;i++)numtype[i]=1;
	for(int i=0;i<SudokuSize;i++){
		catchnum=map[i];
		if(catchnum!=0)numtype[catchnum-1]=0;
	}
	for(int i=0;i<9;i++)numtypeSum=numtypeSum+numtype[i];
	if(numtypeSum>1)return false;
	

	return true;
}*/









void Sudoku::solve(){
	bool nosol;
	int index,element=0;
	int posib[81][9];
	int square[9][9];
	int row[9][9];
	int col[9][9];
	int numChoice[81];
	int scan=0;
	candiSol=0;
	for(int i=0;i<SudokuSize;i++)ANS[i]=0;
	/*for(int i=0;i<81;i++)
		for(int j=0;j<9;j++)map[i]==0?posib[i][j]=1:posib[i][j]=0;*/
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){square[i][j]=0;row[i][j]=0;col[i][j]=0;}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			index=9*i+j;
			element=map[index];
			row[index/9][index%9]=element;
			col[index%9][index/9]=element;
			square[3*(i/3)+(j/3)][3*(i%3)+(j%3)]=element;
		}
	}

	for(int i=0;i<SudokuSize;i++)solmap[i]=map[i];
	bool hasnosol;



	/*for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<square[i][j];
		}
		cout<<endl;
	}*/
	/*multi=prejudge();
	if(multi==false){cout<<2<<endl;return;}*/
	//for(int i=0;i<81;i++)numChoice[i]=0;


	/*nosol=preCheck(posib,row,col,square);
	if(nosol==false){cout<<"0"<<endl;return;}*/
	/*for(int i=0;i<81;i++){
		candi=0;
		for(int j=0;j<9;j++){
			if(posib[i][j]!=0)candi++;
		}
		numChoice[i]=candi;
	}*/
	hasnosol=preCheck(posib,row,col,square);
	if(hasnosol==false){cout<<"0"<<endl;return;}
	//checker(posib,row,col,square);
	if(checknoSol(posib,row,col,square)){cout<<"0"<<endl;return;}
	if(invalid(row,col,square)){cout<<"0"<<endl;return;}
	backtrace(posib,row,col,square,scan);

	if(candiSol==1){
		cout<<1<<endl;
		for(int i=0;i<SudokuSize;i++){
			i%9==8?cout<<ANS[i]<<endl:cout<<ANS[i]<<" ";
		}
	}
	else if(candiSol==0)cout<<"0"<<endl;
	else if(candiSol>1)cout<<"2"<<endl;





}


bool Sudoku::checknoSol(int posib[][9],int row[][9], int col[][9], int square[][9]){
	int count=0;
	int init=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			count=0;
			init=0;

			for(int k=0;k<9;k++){
				if(row[j][k]==i+1)init=1;
			}
			if(init==1)continue;
			for(int k=0;k<9;k++){
				if(posib[9*j+k][i]==1)count++;
			}
			if(count==0)return true;
		}
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			count=0;
			init=0;

			for(int k=0;k<9;k++){
				if(col[j][k]==i+1)init=1;
			}
			if(init==1)continue;
			for(int k=0;k<9;k++){
				if(posib[j+9*k][i]==1)count++;
			}
			if(count==0)return true;
		}
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			count=0;
			init=0;

			for(int k=0;k<9;k++){
				if(square[j][k]==i+1)init=1;
			}
			if(init==1)continue;
			for(int k=0;k<9;k++){
				if(posib[27*(j/3)+3*(j%3)+9*(k/3)+(k%3)][i]==1)count++;
			}
				if(count==0)return true;
		}
	}
	return false;
}



bool Sudoku::invalid(int row[][9], int col[][9], int square[][9]){
	int numrep[9];
	for(int i=0;i<9;i++)numrep[i]=0;
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)numrep[j]=0;
		for(int j=0;j<9;j++){
			if(row[i][j]!=0)numrep[row[i][j]-1]=numrep[row[i][j]-1]+1;
		}
		for(int j=0;j<9;j++)if(numrep[j]>1)return true;
	}

			for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)numrep[j]=0;
		for(int j=0;j<9;j++){
			if(col[i][j]!=0)numrep[col[i][j]-1]=numrep[col[i][j]-1]+1;
		}
		for(int j=0;j<9;j++)if(numrep[j]>1)return true;
	}

			for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)numrep[j]=0;
		for(int j=0;j<9;j++){
			if(square[i][j]!=0)numrep[square[i][j]-1]=numrep[square[i][j]-1]+1;
		}
		for(int j=0;j<9;j++)if(numrep[j]>1)return true;
	}
			return false;
}








bool Sudoku::preCheck(int posib[][9], int row[][9], int col[][9], int square[][9]){
	int indrow,indcol=0;
	int num=0;
	bool nosol;
	int count=0;
	int change=0;
	int geti,getj=0;
	for(int i=0;i<81;i++)
		for(int j=0;j<9;j++)map[i]==0?posib[i][j]=1:posib[i][j]=0;




	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(square[i][j]!=0){
				for(int k=0;k<9;k++){
					posib[27*(i/3)+3*(i%3)+9*(k/3)+(k%3)][square[i][j]-1]=0;
				}
			}
		}
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			
			if(row[i][j]!=0){
				for(int k=0;k<9;k++){
					posib[9*i+k][row[i][j]-1]=0;
				}
			}

			if(col[i][j]!=0){
				for(int k=0;k<9;k++){
					posib[i+9*k][col[i][j]-1]=0;
				}
			}
		}
	}
	/*int	ct=0;
	for(int i=0;i<81;i++){
		cout<<i<<" ";
		for(int j=0;j<9;j++){
			if(posib[i][j]!=0)ct++;
			cout<<posib[i][j];
		}
		cout<<endl;
	}*/

//	cout<<"!!!!!!!: "<<ct<<endl;

	for(int i=0;i<81;i++){
		nosol=0;count=0;
		for(int j=0;j<9;j++){
			if(posib[i][j]!=0){getj=j;count++;nosol=1;}
		}
		if(solmap[i]==0&&nosol==0)return false;
		if(count==1){geti=i;solmap[i]=getj+1;posib[i][getj]=0;change=1;}
	}
	//cout<<endl;
	if(change==1){
		indrow=geti/9;
		indcol=geti%9;
		element2=solmap[geti];
		row[indrow][indcol]=element2;
		col[indcol][indrow]=element2;
		square[3*(indrow/3)+(indcol/3)][3*(indrow%3)+(indcol%3)]=element2;

		//cout<<"!!!!!!!    "<<row[indrow][indcol]<<"!!!!!!!"<<endl;
		//for(int i=0;i<81;i++)i%9!=8?cout<<solmap[i]<<" ":cout<<solmap[i]<<endl;
		return preCheck(posib,row,col,square);
		//cout<<row[indrow][indcol]<<endl;
		

	}



	return true;
}



void Sudoku::checker(int posib[][9], int row[][9], int col[][9], int square[][9]){


	for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
		if(square[i][j]!=0){
			for(int k=0;k<9;k++){
				posib[27*(i/3)+3*(i%3)+9*(k/3)+(k%3)][square[i][j]-1]=0;
				}
			}
		}
	}

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			
				if(row[i][j]!=0){
					for(int k=0;k<9;k++){
						posib[9*i+k][row[i][j]-1]=0;
						}
					}
			
				if(col[i][j]!=0){
					for(int k=0;k<9;k++){
						posib[i+9*k][col[i][j]-1]=0;
						}
					}
			}
		}


}




void Sudoku::backtrace(int posib[][9],int row[][9], int col[][9], int square[][9], int scan ){
	bool SigAns=0;
	if(scan==81){
		candiSol++;
		//cout<<"1"<<endl;
		for(int i=0;i<SudokuSize;i++){
			ANS[i]=solmap[i];
		}
		return;
	}
	if(candiSol<2&&solmap[scan]==0){
		for(int i=0;i<9;i++){
			if(posib[scan][i]==1){
				solmap[scan]=i+1;
				row[scan/9][scan%9]=i+1;
				col[scan%9][scan/9]=i+1;
				square[3*((scan/9)/3)+((scan%9)/3)][3*((scan/9)%3)+((scan%9)%3)]=i+1;
			for(int i=0;i<81;i++){
				for(int j=0;j<9;j++){
					posib[i][j]=1;
				}
			}


				checker(posib,row,col,square);
				backtrace(posib,row,col,square,scan+1);

			}
		}
		solmap[scan]=0;
		row[scan/9][scan%9]=0;
		col[scan%9][scan/9]=0;
		square[3*((scan/9)/3)+((scan%9)/3)][3*((scan/9)%3)+((scan%9)%3)]=0;
		for(int i=0;i<81;i++){
			for(int j=0;j<9;j++){
				posib[i][j]=1;
			}
		}

		checker(posib,row,col,square);
	}

	else if(candiSol<2){
		backtrace(posib,row,col,square,scan+1);
	}




}
		
	














