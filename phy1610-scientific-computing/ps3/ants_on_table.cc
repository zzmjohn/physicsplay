/**
   \file ants_on_table.cc
 */
#include "ants_on_table.h"
#include "optticktock.h"
#include <cmath>
#include <iostream>
#include <cassert>

ants_on_table::ants_on_table( const size_t table_grid_size ) :
   m_table_grid_size( table_grid_size ),
   m_number_of_ants( table_grid_size ),
   m_velocity_x_of_ants( table_grid_size ),
   m_velocity_y_of_ants( table_grid_size ),
   m_timerData{},
   m_new_number_of_ants( table_grid_size )
{
   assert( table_grid_size > 1 ) ;
}

ants_on_table::~ants_on_table( )
{
   #if defined USE_TICK_TOCK
      std::cout << "totants time: \t" << m_timerData.m_totants << std::endl ;
      std::cout << "init time: \t"    << m_timerData.m_init    << std::endl ;
      std::cout << "core time: \t"    << m_timerData.m_core    << std::endl ;
      std::cout << "update time: \t"  << m_timerData.m_update  << std::endl ;
   #endif
}

float ants_on_table::total_number_of_ants() const
{
   TickTockOrNoOp timer ;

   timer.tick() ;

   float totants = m_number_of_ants.sum() ;

   m_timerData.m_totants += timer.silent_tock() ;

   return totants ;
}
