#include <Arduino.h>
#include <concepts>

#pragma once
#ifndef _TIMERS_H
#define _TIMERS_H

#define TIMSK(n) _SFR_MEM8(110 + n)
/// @brief The Timer class template is a C++ wrapper for the Arduino Mega timers.
// Run the isr function every time the timer period ends.
///
/// @tparam[in] N : timer number, there are 5 timers built-in on the arduino mega
template< uint8_t N > class Timer{
  static_assert( (N>0)&&(N<6),"only 5 timers on Arduino mega" );
  static inline uint64_t counter {},interval {1000};
  friend void Routine<N>(); 
public:
  /// @brief enables the timer and call the isr function (if not nullptr)
  static void enableTimer(){ 
    if( isr ) TIMSK(N) = TIMSK(N) | 0b01;
    if constexpr ( N==1 ){ TCCR1A = 0; TCCR1B = 0; TCCR1B = TCCR1B | 0b01; TCNT1 = 49536;  }
    else if constexpr ( N==2 ){ TCCR2A = 0; TCCR2B = 0; TCCR2B = TCCR2B | 0b100;   TCNT2 = 6;   }
    else if constexpr ( N==3 ){ TCCR3A = 0; TCCR3B = 0; TCCR3B = TCCR3B | 0b01; TCNT3 = 49536;  }
    else if constexpr ( N==4 ){ TCCR4A = 0; TCCR4B = 0; TCCR4B = TCCR4B | 0b01; TCNT4 = 49536;  }
    else if constexpr ( N==5 ){ TCCR5A = 0; TCCR5B = 0; TCCR5B = TCCR5B | 0b01; TCNT5 = 49536;  }      
    }
  /// @brief stops the timer
  static void stopTimer(){ TIMSK(N) = TIMSK(N) & 0b00; counter = 0 ;}
  // interrupt service routine pointer
  static inline void(*isr)() {nullptr};
  /// @brief Set the timer's interval. 
  ///
  /// @param[in] T : timer period in miliseconds. defaults to 1000 (1 second). 
  static void setInterval( std::unsigned_integral auto const &T ){ interval = T; }
};
template<uint8_t N> static void Routine(){
  Timer<N>::counter++;  
  if (Timer<N>::counter == Timer<N>::interval){
    Timer<N>::isr(); Timer<N>::counter = 0;
  }
  if   constexpr    ( N == 1 ){ TCNT1 = 49536; }  
  else if constexpr ( N == 2 ){   TCNT2 = 6;   }  
  else if constexpr ( N == 3 ){ TCNT3 = 49536; }  
  else if constexpr ( N == 4 ){ TCNT4 = 49536; }  
  else if constexpr ( N == 5 ){ TCNT5 = 49536; }  
}

#endif
