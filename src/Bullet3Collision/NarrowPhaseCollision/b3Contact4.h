/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2013 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef B3_CONTACT4_H
#define B3_CONTACT4_H

#include "Bullet3Common/b3Vector3.h"


B3_ATTRIBUTE_ALIGNED16(struct) b3Contact4
{
	B3_DECLARE_ALIGNED_ALLOCATOR();

	b3Vector3	m_worldPos[4];
	b3Vector3	m_worldNormal;
//	float m_restituitionCoeff;
//	float m_frictionCoeff;
	unsigned short  m_restituitionCoeffCmp;
	unsigned short  m_frictionCoeffCmp;
	int m_batchIdx;

	int m_bodyAPtrAndSignBit;
	int m_bodyBPtrAndSignBit;

	int getBodyA()const {return abs(m_bodyAPtrAndSignBit);}
	int getBodyB()const {return abs(m_bodyBPtrAndSignBit);}
	bool isBodyAFixed()const { return m_bodyAPtrAndSignBit<0;}
	bool isBodyBFixed()const { return m_bodyBPtrAndSignBit<0;}
	//	todo. make it safer
	int& getBatchIdx() { return m_batchIdx; }
	const int& getBatchIdx() const { return m_batchIdx; }
	float getRestituitionCoeff() const { return ((float)m_restituitionCoeffCmp/(float)0xffff); }
	void setRestituitionCoeff( float c ) { b3Assert( c >= 0.f && c <= 1.f ); m_restituitionCoeffCmp = (unsigned short)(c*0xffff); }
	float getFrictionCoeff() const { return ((float)m_frictionCoeffCmp/(float)0xffff); }
	void setFrictionCoeff( float c ) { b3Assert( c >= 0.f && c <= 1.f ); m_frictionCoeffCmp = (unsigned short)(c*0xffff); }

	float& getNPoints() { return m_worldNormal[3]; }
	float getNPoints() const { return m_worldNormal[3]; }

	float getPenetration(int idx) const { return m_worldPos[idx][3]; }

	bool isInvalid() const { return (getBodyA()==0 || getBodyB()==0); }
};

#endif //B3_CONTACT4_H
