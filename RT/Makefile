# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 19:14:50 by yvikhrov          #+#    #+#              #
#    Updated: 2019/02/01 12:28:04 by yvikhrov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FULL_PATH=$(shell pwd)
BUILD_PATH=$(FULL_PATH)/build
XCODE_PATH=$(FULL_PATH)/buildXcode
CMAKE_DEFINES="-DBUILD_SHARED_LIBS=OFF"
NAME=RT

all: configure $(NAME)

$(NAME):
	@cmake --build $(BUILD_PATH) --config Release --target $(NAME) -- -j4

configure:
	@cmake -DFULL_PATH="$(FULL_PATH)" \
		   -B"$(BUILD_PATH)" \
		   -H"$(FULL_PATH)" \
		   $(CMAKE_DEFINES)

configure_xcode:
	@cmake -G "Xcode" \
		   -DFULL_PATH="$(FULL_PATH)" \
		   -B"$(XCODE_PATH)" \
		   -H"$(FULL_PATH)" \
		   $(CMAKE_DEFINES)

xcode: configure_xcode
	@open "$(shell find $(XCODE_PATH) -maxdepth 1 -name "*.xcodeproj")"

clean:
	@rm -rf $(BUILD_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean all clean
