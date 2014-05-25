#include "stdafx.h"
#include "InformationDraw.h"
#include <iostream>

using namespace std;

InformationDraw::InformationDraw(){

}
InformationDraw::InformationDraw(bool init){
	initFlag = init;
}


void InformationDraw::setNumberOfParent(int number){
	numberOfParent = number;
}
void InformationDraw::setInformationSize(int size){
	informationClass.resize(size);
}

int InformationDraw::IdGenerator(int parentNumber, int childNumber,int orderNumber, int identifier){

	
/*
	01: 속성
	00x: 면번째 line 인지
	00: 몇번쨰 sheet 인지
	00: 몇번쨰 부모인지
	1: default

	default * 1000000000
	부모 * 10000000
	시트 * 100000
	몇번째 * 100
	속성 * 1
*/



	return 1*1000000000   +   parentNumber*10000000  +   childNumber*100000   +   orderNumber*100  +   identifier;

}


/////////그리는 부분/////////
void InformationDraw::drawInformation(int parentIndex){

	int i,j;
	//점


	for(i = 0; i < informationClass[parentIndex].getNumberOfChild(); i++){	//해당 부모노드의 자식의 0부터 ..

		if(informationClass[parentIndex].isChildClicked(i)){  //자식 노드가 클릭(체크)되어있으면 그림
		
			for(j = 0; j <= informationClass[parentIndex].pointClass[i].getLastIndex(); j++){	//점그려주는 부분

				
				
						//ID 네임스택에 넣음
					glPushMatrix();
					glPushName(informationClass[parentIndex].pointClass[i].getPointID(j));	
					
						//색상지정
					glColor3f(informationClass[parentIndex].pointClass[i].getPointColorRed(j),informationClass[parentIndex].pointClass[i].getPointColorGreen(j),informationClass[parentIndex].pointClass[i].getPointColorBlue(j));
					glTranslatef(informationClass[parentIndex].pointClass[i].getPointX(j), informationClass[parentIndex].pointClass[i].getPointY(j), informationClass[parentIndex].pointClass[i].getPointZ(j)+0.001);
					auxSolidSphere(informationClass[parentIndex].pointClass[i].getPointSize(j));	
					   
					glPopName();
					glPopMatrix();
			}



			//선(line)그려주는 부분...그려주는 것을 선분이 아니라, 사각형으로 해야 하나..

			for(j = 0; j <= informationClass[parentIndex].linesClass[i].getLastIndex(); j++){	//점그려주는 부분  i번째 자식의 라인이 몇개를 가지고 있는 수 까지 .. 라인을 그려줌 
					
						//ID 네임스택에 넣음
					glPushMatrix();
					glPushName(informationClass[parentIndex].linesClass[i].getLineID(j));//해당 라인의 아이디 넣어줌	

						//색상지정
					
					
					//라인 굵기 설정
					glLineWidth(informationClass[parentIndex].linesClass[i].getLineSize(j));
					glBegin(GL_LINE_STRIP);{	//선 그리는 옵션
					glColor3f(informationClass[parentIndex].linesClass[i].getLineColorRed(j),informationClass[parentIndex].linesClass[i].getLineColorGreen(j),informationClass[parentIndex].linesClass[i].getLineColorBlue(j));
						for(int k = 0; k < informationClass[parentIndex].linesClass[i].lineClass[j].getNumberOfLinePoints() ; k++){	//그 라인이 몇개의 점으로 이루어 져 있는지 알아야함.
							float* point;		//라인 굵기, 패턴...도 설정해야.
							point = informationClass[parentIndex].linesClass[i].lineClass[j].getPointXYZ(k);
							glVertex3f(point[0], point[1], point[2]+0.001);

						}
						
					}glEnd();
					
					glPopName();
					glPopMatrix();
					
						glPushMatrix();


					//입체감을 주기 위한 선 그려주기
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1,0xAAAA);
					glBegin(GL_LINES);{	//선 그리는 옵션
					glColor3f(informationClass[parentIndex].linesClass[i].getLineColorRed(j),informationClass[parentIndex].linesClass[i].getLineColorGreen(j),informationClass[parentIndex].linesClass[i].getLineColorBlue(j));
						for(int k = 0; k < informationClass[parentIndex].linesClass[i].lineClass[j].getNumberOfLinePoints() ; k++){	//그 라인이 몇개의 점으로 이루어 져 있는지 알아야함.
							float* point;		//라인 굵기, 패턴...도 설정해야.
							point = informationClass[parentIndex].linesClass[i].lineClass[j].getPointXYZ(k);
							glVertex3f(point[0], point[1], point[2]+0.001);
							glVertex3f(point[0], point[1], point[2]);

						}
					
					}glEnd();
					glDisable(GL_LINE_STIPPLE);
					glPopMatrix();
			}

			//폴리곤 그려주는 부분

					for(j = 0; j <= informationClass[parentIndex].polygonsClass[i].getLastIndex(); j++){	//점그려주는 부분  i번째 자식의 라인이 몇개를 가지고 있는 수 까지 .. 라인을 그려줌 
					
					//ID 네임스택에 넣음
				glPushMatrix();
				glPushName(informationClass[parentIndex].polygonsClass[i].getPolygonID(j));//해당 라인의 아이디 넣어줌	
				
				glBegin(GL_POLYGON);{	//폴리곤 그리는 옵션
					//색상지정
					glColor3f(informationClass[parentIndex].polygonsClass[i].getPolygonColorRed(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorGreen(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorBlue(j));
					
					
					for(int k = 0; k < informationClass[parentIndex].polygonsClass[i].polygonClass[j].getNumberOfPolygonPoints() ; k++){	//그 폴리곤이 몇개의 점으로 이루어 져 있는지 알아야함.
						float* point;		//라인 굵기, 패턴...도 설정해야.
						point = informationClass[parentIndex].polygonsClass[i].polygonClass[j].getPolygonPointXYZ(k);
						glVertex3f(point[0], point[1], POLYGON_HEIGHT);

					}
						
				}glEnd();
					
				glPopName();
				glPopMatrix();
					



				glPushMatrix();
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(1,0xAAAA);
				glBegin(GL_LINES);{	//폴리곤 그리는 옵션
					//색상지정
					glColor3f(informationClass[parentIndex].polygonsClass[i].getPolygonColorRed(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorGreen(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorBlue(j));
					
					
					for(int k = 0; k < informationClass[parentIndex].polygonsClass[i].polygonClass[j].getNumberOfPolygonPoints() ; k++){	//그 폴리곤이 몇개의 점으로 이루어 져 있는지 알아야함.
						float* point;		//라인 굵기, 패턴...도 설정해야.
						point = informationClass[parentIndex].polygonsClass[i].polygonClass[j].getPolygonPointXYZ(k);
						glVertex3f(point[0], point[1], POLYGON_HEIGHT);
						glVertex3f(point[0], point[1], point[2]);
					}
						
				}glEnd();
					
			
				glPopMatrix();
				glDisable(GL_LINE_STIPPLE);
				/*
				glPushMatrix();	
				//입체감을 주기 위한 선 그려주기
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(1,0xAAAA);
				glBegin(GL_LINES);{	//선 그리는 옵션
				glColor3f(informationClass[parentIndex].polygonsClass[i].getPolygonColorRed(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorGreen(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorBlue(j));
					for(int k = 0; k < informationClass[parentIndex].polygonsClass[i].polygonClass[j].getNumberOfPolygonPoints() ; k++){	//그 라인이 몇개의 점으로 이루어 져 있는지 알아야함.
						float* point;		//라인 굵기, 패턴...도 설정해야.
						point = informationClass[parentIndex].linesClass[i].lineClass[j].getPointXYZ(k);
						glVertex3f(point[0], point[1], POLYGON_HEIGHT);
						glVertex3f(point[0], point[1], point[2]);

					}
					
				}glEnd();
				glDisable(GL_LINE_STIPPLE);
				glPopMatrix();
			
			*/
			}
			



		}
		
		
	
	}

	//선


	//원


	//다각형

}



int InformationDraw::getNumberOfParent(void){

	return numberOfParent;
}
