#ifndef _WT_RELATIONINFO_H__
#define _WT_RELATIONINFO_H__

#include "Globals.h"

struct RelationTypeId {
	
	explicit RelationTypeId(uint32_t id = 0):m_rid(id) {}
	RelationTypeId& operator = (uint32_t id) { m_rid = id; return *this; }

	 bool operator == (const RelationTypeId& o) const { return m_rid == o.m_rid; }
	 bool operator != (const RelationTypeId& o) const { return m_rid != o.m_rid; }
	 bool operator < (const RelationTypeId& o) const { return m_rid < o.m_rid; }
	 bool operator > (const RelationTypeId& o) const { return m_rid > o.m_rid; }
	 bool operator <= (const RelationTypeId& o) const { return m_rid <= o.m_rid; }
	 bool operator >= (const RelationTypeId& o) const { return m_rid >= o.m_rid; }	
	
	 uint32_t AsInt() const { return m_rid;}
	 
	uint32_t m_rid;
};

template <uint32_t rid>
struct RelationTypeIdT: public RelationTypeId {
	explicit RelationTypeIdT():RelationTypeId(rid) {}
};

struct RelationType {

	enum Direction {
		DIR_INVALID = -1,
		DIR_FORWARD = 0,
		DIR_BACKWARD = 1,
		DIR_BIDIRECTIONAL = 2
	};
	
	RelationType():m_dir(DIR_FORWARD), m_relId(0) {}
	RelationType(RelationTypeId id):m_dir(DIR_FORWARD), m_relId(id) {}
	RelationType(RelationTypeId id, Direction dir):m_dir(dir), m_relId(0) {}

	 bool operator == (const RelationType& o) const 
	  { return (m_dir == o.m_dir && m_relId == o.m_relId); }
	 
	 bool operator != (const RelationType& o) const 
	  { return !(this->operator == (o)); }
	 
	 bool operator < (const RelationType& o) const
	 {
	  if (m_dir == o.m_dir)
	   return m_relId < o.m_relId;
	  else
	   return m_dir < o.m_dir;
	 }
	
	
	 RelationType& ReverseDir()
	 {
	  if (m_dir != DIR_BIDIRECTIONAL)
	   m_dir = (Direction)(DIR_BACKWARD - m_dir);
	  return *this;
	 }
	
	 uint32_t Id() const { return m_relId.AsInt();}
	 
	Direction m_dir;
	RelationTypeId m_relId;
} ;

typedef RelationTypeIdT<0x00000010> ParentChild ;

typedef RelationTypeIdT<0x00000100> BottomMostHeader; 
typedef RelationTypeIdT<0x00000101> StackedOnHeader ;
typedef RelationTypeIdT<0x00000102> TopMostHeader ;

typedef RelationTypeIdT<0x00000110> FirstPacket; 
typedef RelationTypeIdT<0x00000111> StackedOnPacket; 
typedef RelationTypeIdT<0x00000112> LastPacket; 


#endif /*_WT_RELATIONINFO_H__*/
