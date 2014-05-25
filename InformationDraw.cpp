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
	01: �Ӽ�
	00x: ���° line ����
	00: ����� sheet ����
	00: ����� �θ�����
	1: default

	default * 1000000000
	�θ� * 10000000
	��Ʈ * 100000
	���° * 100
	�Ӽ� * 1
*/



	return 1*1000000000   +   parentNumber*10000000  +   childNumber*100000   +   orderNumber*100  +   identifier;

}


/////////�׸��� �κ�/////////
void InformationDraw::drawInformation(int parentIndex){

	int i,j;
	//��


	for(i = 0; i < informationClass[parentIndex].getNumberOfChild(); i++){	//�ش� �θ����� �ڽ��� 0���� ..

		if(informationClass[parentIndex].isChildClicked(i)){  //�ڽ� ��尡 Ŭ��(üũ)�Ǿ������� �׸�
		
			for(j = 0; j <= informationClass[parentIndex].pointClass[i].getLastIndex(); j++){	//���׷��ִ� �κ�

				
				
						//ID ���ӽ��ÿ� ����
					glPushMatrix();
					glPushName(informationClass[parentIndex].pointClass[i].getPointID(j));	
					
						//��������
					glColor3f(informationClass[parentIndex].pointClass[i].getPointColorRed(j),informationClass[parentIndex].pointClass[i].getPointColorGreen(j),informationClass[parentIndex].pointClass[i].getPointColorBlue(j));
					glTranslatef(informationClass[parentIndex].pointClass[i].getPointX(j), informationClass[parentIndex].pointClass[i].getPointY(j), informationClass[parentIndex].pointClass[i].getPointZ(j)+0.001);
					auxSolidSphere(informationClass[parentIndex].pointClass[i].getPointSize(j));	
					   
					glPopName();
					glPopMatrix();
			}



			//��(line)�׷��ִ� �κ�...�׷��ִ� ���� ������ �ƴ϶�, �簢������ �ؾ� �ϳ�..

			for(j = 0; j <= informationClass[parentIndex].linesClass[i].getLastIndex(); j++){	//���׷��ִ� �κ�  i��° �ڽ��� ������ ��� ������ �ִ� �� ���� .. ������ �׷��� 
					
						//ID ���ӽ��ÿ� ����
					glPushMatrix();
					glPushName(informationClass[parentIndex].linesClass[i].getLineID(j));//�ش� ������ ���̵� �־���	

						//��������
					
					
					//���� ���� ����
					glLineWidth(informationClass[parentIndex].linesClass[i].getLineSize(j));
					glBegin(GL_LINE_STRIP);{	//�� �׸��� �ɼ�
					glColor3f(informationClass[parentIndex].linesClass[i].getLineColorRed(j),informationClass[parentIndex].linesClass[i].getLineColorGreen(j),informationClass[parentIndex].linesClass[i].getLineColorBlue(j));
						for(int k = 0; k < informationClass[parentIndex].linesClass[i].lineClass[j].getNumberOfLinePoints() ; k++){	//�� ������ ��� ������ �̷�� �� �ִ��� �˾ƾ���.
							float* point;		//���� ����, ����...�� �����ؾ�.
							point = informationClass[parentIndex].linesClass[i].lineClass[j].getPointXYZ(k);
							glVertex3f(point[0], point[1], point[2]+0.001);

						}
						
					}glEnd();
					
					glPopName();
					glPopMatrix();
					
						glPushMatrix();


					//��ü���� �ֱ� ���� �� �׷��ֱ�
					glEnable(GL_LINE_STIPPLE);
					glLineStipple(1,0xAAAA);
					glBegin(GL_LINES);{	//�� �׸��� �ɼ�
					glColor3f(informationClass[parentIndex].linesClass[i].getLineColorRed(j),informationClass[parentIndex].linesClass[i].getLineColorGreen(j),informationClass[parentIndex].linesClass[i].getLineColorBlue(j));
						for(int k = 0; k < informationClass[parentIndex].linesClass[i].lineClass[j].getNumberOfLinePoints() ; k++){	//�� ������ ��� ������ �̷�� �� �ִ��� �˾ƾ���.
							float* point;		//���� ����, ����...�� �����ؾ�.
							point = informationClass[parentIndex].linesClass[i].lineClass[j].getPointXYZ(k);
							glVertex3f(point[0], point[1], point[2]+0.001);
							glVertex3f(point[0], point[1], point[2]);

						}
					
					}glEnd();
					glDisable(GL_LINE_STIPPLE);
					glPopMatrix();
			}

			//������ �׷��ִ� �κ�

					for(j = 0; j <= informationClass[parentIndex].polygonsClass[i].getLastIndex(); j++){	//���׷��ִ� �κ�  i��° �ڽ��� ������ ��� ������ �ִ� �� ���� .. ������ �׷��� 
					
					//ID ���ӽ��ÿ� ����
				glPushMatrix();
				glPushName(informationClass[parentIndex].polygonsClass[i].getPolygonID(j));//�ش� ������ ���̵� �־���	
				
				glBegin(GL_POLYGON);{	//������ �׸��� �ɼ�
					//��������
					glColor3f(informationClass[parentIndex].polygonsClass[i].getPolygonColorRed(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorGreen(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorBlue(j));
					
					
					for(int k = 0; k < informationClass[parentIndex].polygonsClass[i].polygonClass[j].getNumberOfPolygonPoints() ; k++){	//�� �������� ��� ������ �̷�� �� �ִ��� �˾ƾ���.
						float* point;		//���� ����, ����...�� �����ؾ�.
						point = informationClass[parentIndex].polygonsClass[i].polygonClass[j].getPolygonPointXYZ(k);
						glVertex3f(point[0], point[1], POLYGON_HEIGHT);

					}
						
				}glEnd();
					
				glPopName();
				glPopMatrix();
					



				glPushMatrix();
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(1,0xAAAA);
				glBegin(GL_LINES);{	//������ �׸��� �ɼ�
					//��������
					glColor3f(informationClass[parentIndex].polygonsClass[i].getPolygonColorRed(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorGreen(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorBlue(j));
					
					
					for(int k = 0; k < informationClass[parentIndex].polygonsClass[i].polygonClass[j].getNumberOfPolygonPoints() ; k++){	//�� �������� ��� ������ �̷�� �� �ִ��� �˾ƾ���.
						float* point;		//���� ����, ����...�� �����ؾ�.
						point = informationClass[parentIndex].polygonsClass[i].polygonClass[j].getPolygonPointXYZ(k);
						glVertex3f(point[0], point[1], POLYGON_HEIGHT);
						glVertex3f(point[0], point[1], point[2]);
					}
						
				}glEnd();
					
			
				glPopMatrix();
				glDisable(GL_LINE_STIPPLE);
				/*
				glPushMatrix();	
				//��ü���� �ֱ� ���� �� �׷��ֱ�
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(1,0xAAAA);
				glBegin(GL_LINES);{	//�� �׸��� �ɼ�
				glColor3f(informationClass[parentIndex].polygonsClass[i].getPolygonColorRed(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorGreen(j),informationClass[parentIndex].polygonsClass[i].getPolygonColorBlue(j));
					for(int k = 0; k < informationClass[parentIndex].polygonsClass[i].polygonClass[j].getNumberOfPolygonPoints() ; k++){	//�� ������ ��� ������ �̷�� �� �ִ��� �˾ƾ���.
						float* point;		//���� ����, ����...�� �����ؾ�.
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

	//��


	//��


	//�ٰ���

}



int InformationDraw::getNumberOfParent(void){

	return numberOfParent;
}
