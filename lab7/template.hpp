//
//  template.hpp
//  lab7
//
//  Created by 邱煜 on 2019/5/26.
//  Copyright © 2019 邱煜. All rights reserved.
//

#ifndef template_hpp
#define template_hpp

// primary template
template <typename, typename = std::void_t<> >
struct is_incrementable : std::false_type{ };

// specialization
template <typename T>
struct is_incrementable<T, std::void_t<decltype(std::declval<T&>()++), decltype(++std::declval<T&>())>
> : std::true_type { };

#endif /* template_hpp */
