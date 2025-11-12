/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:55:22 by phhofman          #+#    #+#             */
/*   Updated: 2025/11/12 14:04:33 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class User
{
private:
    std::string _nickname;
    bool _is_op;
    int _fd;

public:
    User();
    User(const std::string &nickname, bool is_op, int fd);
    User(const User &other);
    User &operator=(const User &other);
    ~User();
};