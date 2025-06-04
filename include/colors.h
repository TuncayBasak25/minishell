/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 07:00:23 by rel-hass          #+#    #+#             */
/*   Updated: 2025/03/04 07:01:09 by rel-hass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Réinitialisation
# define RESET       "\033[0m"

// Styles
# define BOLD        "\033[1m"
# define DIM         "\033[2m"
# define ITALIC      "\033[3m"
# define UNDERLINE   "\033[4m"
# define BLINK       "\033[5m"
# define REVERSE     "\033[7m"
# define HIDDEN      "\033[8m"

// Couleurs texte
# define BLACK       "\033[0;30m"
# define RED         "\033[0;31m"
# define GREEN       "\033[0;32m"
# define YELLOW      "\033[0;33m"
# define BLUE        "\033[0;34m"
# define MAGENTA     "\033[0;35m"
# define CYAN        "\033[0;36m"
# define WHITE       "\033[0;37m"

// Couleurs texte en gras
# define BBLACK      "\033[1;30m"
# define BRED        "\033[1;31m"
# define BGREEN      "\033[1;32m"
# define BYELLOW     "\033[1;33m"
# define BBLUE       "\033[1;34m"
# define BMAGENTA    "\033[1;35m"
# define BCYAN       "\033[1;36m"
# define BWHITE      "\033[1;37m"

// Couleurs de fond
# define BG_BLACK    "\033[40m"
# define BG_RED      "\033[41m"
# define BG_GREEN    "\033[42m"
# define BG_YELLOW   "\033[43m"
# define BG_BLUE     "\033[44m"
# define BG_MAGENTA  "\033[45m"
# define BG_CYAN     "\033[46m"
# define BG_WHITE    "\033[47m"

// Couleurs de fond vives
# define BG_BBLACK   "\033[100m"
# define BG_BRED     "\033[101m"
# define BG_BGREEN   "\033[102m"
# define BG_BYELLOW  "\033[103m"
# define BG_BBLUE    "\033[104m"
# define BG_BMAGENTA "\033[105m"
# define BG_BCYAN    "\033[106m"
# define BG_BWHITE   "\033[107m"

#endif
