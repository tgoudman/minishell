------------------------------- FAIL TEST ---------------------------------

CMD[0] input [0] output [1] : [ls]
CMD[1] input [0] output [1] : [ls]
CMD[2] input [0] output [1] : [ls][-l]
CMD[3] input [0] output [1] : [ ]
LINE after parsing is : 0 | !ok | 1 | !ok | !ok | 2 | !ok | 3 !ok | !ok 
minishell: Command ' ' not found
Input : ls | <ok | ls | <ok |>ok |  ls -l | >ok | >ok | <ok

 ---------------------------------------------------------

CMD[0] input [0] output [1] : [echo][test]
CMD[1] input [0] output [1] : [rev]
CMD[2] input [0] output [1] : [ tee][output.txt]
LINE after parsing is : 0 | 1 | 2 
minishell: Command ' tee' not found
Input : echo test | rev | tee output.txt

---------------------------------------------------------

CMD[0] input [0] output [1] : [echo][test]
CMD[1] input [0] output [1] : [ rev]
LINE after parsing is : 0 | 1 !ok 
execute cmd echo in (null)
execute cmd (null) in (null)
minishell: Command ' rev' not found
Input : echo test | rev >ok

----------------------------------------------------------

CMD[0] input [0] output [1] : [echo][thizzzzzzzzt]
CMD[1] input [0] output [1] : [rev]
CMD[2] input [0] output [1] : [rev]
CMD[3] input [0] output [1] : [ rev]
LINE after parsing is : 0 | 1 | 2 !ok | 3 !ok 
execute cmd echo in (null)
execute cmd rev in (null) index is  1
execute cmd rev in !ok index is  2
execute cmd  rev in !ok index is  3
minishell: Command ' rev' not found
Input :  echo thizzzzzzzzt |rev | rev  >ok | rev >ok

---------------------------------------------------------

SUCCESS TEST No leak and no FD open
cat Makefile | rev > ok | rev >oki |<main.c |>>oki |ls | rev
