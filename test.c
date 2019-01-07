/*
 * Copyright (C) 2019 CERN for the benefit of the LHCb collaboration
 * Author: Paul Seyfert <pseyfert@cern.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In applying this licence, CERN does not waive the privileges and immunities
 * granted to it by virtue of its status as an Intergovernmental Organization
 * or submit itself to any jurisdiction.
 */

#include "high.h"
#include <stdio.h>

int main() {

  char* t1 = "hello";
  char* t2 = "hello";
  char* s1 = NULL;
  char* s2 = NULL;
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "helllo";
  t2 = "hello";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "helto";
  t2 = "hello";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "hel%o";
  t2 = "hel%o";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  printf("\033[0m");

  t1 = "hel%o";
  t2 = "hello";
  high(t1, t2, &s1, &s2);
  printf("\"%s\" and \"%s\" turned into \"%s\" and \"%s\"\n", t1, t2, s1, s2);
  free(s1);
  free(s2);

  return 0;
}
