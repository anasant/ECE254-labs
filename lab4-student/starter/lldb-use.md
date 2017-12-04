ter$ make
gcc -MM -MF main_test.d main_test.c
gcc -Wall -g -c main_test.c
main_test.c:31:3: error: void function 'mem_alloc_test' should not return a
      value [-Wreturn-type]
                return best_fit_alloc(size);
                ^      ~~~~~~~~~~~~~~~~~~~~
main_test.c:33:3: error: void function 'mem_alloc_test' should not return a
      value [-Wreturn-type]
                return worst_fit_alloc(size);
                ^      ~~~~~~~~~~~~~~~~~~~~~
main_test.c:58:8: error: initializing 'void *' with an expression of
      incompatible type 'void'
        void* mem = mem_alloc_test(8*1024, algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:72:8: error: initializing 'void *' with an expression of
      incompatible type 'void'
        void* mem = mem_alloc_test(8*1024 - sizeof(node), algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:86:8: error: initializing 'void *' with an expression of
      incompatible type 'void'
        void* mem = mem_alloc_test(7*1024, algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:96:8: error: initializing 'void *' with an expression of
      incompatible type 'void'
        void* mem2 = mem_alloc_test(1024 - sizeof(node), algo);
              ^      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:121:8: error: initializing 'void *' with an expression of
      incompatible type 'void'
        void* mem = mem_alloc_test(7*1024, algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:131:8: error: initializing 'void *' with an expression of
      incompatible type 'void'
        void* mem2 = mem_alloc_test(1024 - sizeof(node), algo);
              ^      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
8 errors generated.
make: *** [main_test.o] Error 1
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF main_test.d main_test.c
gcc -MM -MF mem.d mem.c
gcc -Wall -g -c mem.c
gcc -Wall -g -c main_test.c
main_test.c:31:10: warning: incompatible pointer to integer conversion returning
      'void *' from a function with result type 'int' [-Wint-conversion]
                return best_fit_alloc(size);
                       ^~~~~~~~~~~~~~~~~~~~
main_test.c:33:10: warning: incompatible pointer to integer conversion returning
      'void *' from a function with result type 'int' [-Wint-conversion]
                return worst_fit_alloc(size);
                       ^~~~~~~~~~~~~~~~~~~~~
main_test.c:58:8: warning: incompatible integer to pointer conversion
      initializing 'void *' with an expression of type 'int' [-Wint-conversion]
        void* mem = mem_alloc_test(8*1024, algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:72:8: warning: incompatible integer to pointer conversion
      initializing 'void *' with an expression of type 'int' [-Wint-conversion]
        void* mem = mem_alloc_test(8*1024 - sizeof(node), algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:86:8: warning: incompatible integer to pointer conversion
      initializing 'void *' with an expression of type 'int' [-Wint-conversion]
        void* mem = mem_alloc_test(7*1024, algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:96:8: warning: incompatible integer to pointer conversion
      initializing 'void *' with an expression of type 'int' [-Wint-conversion]
        void* mem2 = mem_alloc_test(1024 - sizeof(node), algo);
              ^      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:120:8: warning: incompatible integer to pointer conversion
      initializing 'void *' with an expression of type 'int' [-Wint-conversion]
        void* mem = mem_alloc_test(7*1024, algo);
              ^     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main_test.c:130:8: warning: incompatible integer to pointer conversion
      initializing 'void *' with an expression of type 'int' [-Wint-conversion]
        void* mem2 = mem_alloc_test(1024 - sizeof(node), algo);
              ^      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
8 warnings generated.
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF main_test.d main_test.c
gcc -Wall -g -c main_test.c
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make clean
rm -f *.d *.o main_test.out
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF main_test.d main_test.c
gcc -MM -MF mem.d mem.c
gcc -Wall -g -c mem.c
gcc -Wall -g -c main_test.c
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ ./
Makefile       main_test.c    main_test.out  mem.c          mem.h
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ ./main_test.out 0
Segmentation fault: 11
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ ./main_test.out 1
Segmentation fault: 11
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ ./main_test.out 0
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ vim Makefile
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) run
Process 2629 launched: './main_test.out' (x86_64)
Process 2629 stopped
* thread #1: tid = 0x24cf6, 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0xffffffffffffffec)
    frame #0: 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
   104 		node* current = (node*) ((size_t)ptr - sizeof(node));
-> 105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
   108 		int previous_free = current->previous && !(current->previous->is_allocated);
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF mem.d mem.c
gcc -Wall -g -c mem.c
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) run
Process 2682 launched: './main_test.out' (x86_64)
Process 2682 stopped
* thread #1: tid = 0x25006, 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0xffffffffffffffec)
    frame #0: 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
   104 		node* current = (node*) ((void*)ptr - (void*)sizeof(node));
-> 105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
   108 		int previous_free = current->previous && !(current->previous->is_allocated);
(lldb) current
error: 'current' is not a valid command.
error: Unrecognized command 'current'.
(lldb) frame
The following subcommands are supported:

      info     -- List information about the currently selected frame in the
                  current thread.
      select   -- Select a frame by index from within the current thread and
                  make it the current frame.
      variable -- Show frame variables. All argument and local variables that
                  are in scope will be shown when no arguments are given. If
                  any arguments are specified, they can be names of argument,
                  local, file static and file global variables. Children of
                  aggregate variables can be specified such as 'var->child.x'.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) frame vars
invalid command 'frame vars'.
(lldb) frame v
(void *) ptr = 0x0000000000000000
(node *) current = 0xffffffffffffffe8
(int) previous_free = 0
(int) next_free = 0
(lldb) bt
* thread #1: tid = 0x25006, 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0xffffffffffffffec)
  * frame #0: 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105
    frame #1: 0x0000000100001275 main_test.out`best_fit_dealloc(ptr=0x0000000000000000) + 21 at mem.c:138
    frame #2: 0x0000000100001412 main_test.out`mem_dealloc_test(ptr=0x0000000000000000, algo=0) + 34 at main_test.c:39
    frame #3: 0x0000000100001547 main_test.out`test_not_split_easy(algo=0) + 215 at main_test.c:66
    frame #4: 0x0000000100001e56 main_test.out`main(argc=2, argv=0x00007fff5fbff648) + 230 at main_test.c:170
    frame #5: 0x00007fffc67ca235 libdyld.dylib`start + 1
    frame #6: 0x00007fffc67ca235 libdyld.dylib`start + 1
(lldb) frame 3
invalid command 'frame 3'.
(lldb) thread
The following subcommands are supported:

      backtrace      -- Show the stack for one or more threads.  If no threads
                        are specified, show the currently selected thread.  Use
                        the thread-index "all" to see all threads.
      continue       -- Continue execution of one or more threads in an active
                        process.
      info           -- Show an extended summary of information about thread(s)
                        in a process.
      jump           -- Sets the program counter to a new address.
      list           -- Show a summary of all current threads in a process.
      plan           -- A set of subcommands for accessing the thread plans
                        controlling execution control on one or more threads.
      return         -- Return from the currently selected frame,
                        short-circuiting execution of the frames below it, with
                        an optional return value, or with the -x option from
                        the innermost function evaluation.  This command takes
                        'raw' input (no need to quote stuff).
      select         -- Select a thread as the currently active thread.
      step-in        -- Source level single step in specified thread (current
                        thread, if none specified).
      step-inst      -- Single step one instruction in specified thread
                        (current thread, if none specified).
      step-inst-over -- Single step one instruction in specified thread
                        (current thread, if none specified), stepping over
                        calls.
      step-out       -- Finish executing the function of the currently selected
                        frame and return to its call site in specified thread
                        (current thread, if none specified).
      step-over      -- Source level single step in specified thread (current
                        thread, if none specified), stepping over calls.
      step-scripted  -- Step as instructed by the script class passed in the -C
                        option.
      until          -- Run the current or specified thread until it reaches a
                        given line number or address or leaves the current
                        function.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) frame
The following subcommands are supported:

      info     -- List information about the currently selected frame in the
                  current thread.
      select   -- Select a frame by index from within the current thread and
                  make it the current frame.
      variable -- Show frame variables. All argument and local variables that
                  are in scope will be shown when no arguments are given. If
                  any arguments are specified, they can be names of argument,
                  local, file static and file global variables. Children of
                  aggregate variables can be specified such as 'var->child.x'.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) frame select 3
frame #3: 0x0000000100001547 main_test.out`test_not_split_easy(algo=0) + 215 at main_test.c:66
   63  		printf("%d", head->next == NULL);
   64  		printf("%d", head->previous == NULL);
   65
-> 66  		mem_dealloc_test(mem, algo);
   67  		printf("\n");
   68  	}
   69
(lldb) frame v
(int) algo = 0
(void *) mem = 0x0000000000000000
(node *) head = 0x0000000101000000
(lldb) head_bf
error: 'head_bf' is not a valid command.
error: Unrecognized command 'head_bf'.
(lldb) expr
Enter expressions, then terminate with an empty line to evaluate:
  1: head_bf
  2: head_wf
  3:
error: expected ';' after expression
error: 1 errors parsing expression
(lldb) expr head_wf
(node *) $0 = 0x0000000000000000
(lldb) expr head_bf
(node *) $1 = 0x0000000101000000
(lldb) expr *(char*) head_bf
(char) $2 = '\0'
(lldb) expr *((char*) head_bf +1)
(char) $3 = ' '
(lldb) expr *((char*) head_bf +2)
(char) $4 = '\0'
(lldb) expr *((char*) head_bf +3)
(char) $5 = '\0'
(lldb) expr *((char*) head_bf +4)
(char) $6 = '\0'
(lldb) expr *((char*) head_bf +5)
(char) $7 = '\0'
(lldb) expr *((char*) head_bf +6)
(char) $8 = '\0'
(lldb) expr *((char*) head_bf +7)
(char) $9 = '\0'
(lldb) expr *((char*) head_bf +8)
(char) $10 = '\0'
(lldb) expr *((char*) head_bf +9)
(char) $11 = '\0'
(lldb) expr *((char*) head_bf +10)
(char) $12 = '\0'
(lldb) expr *((char*) head_bf +11)
(char) $13 = '\0'
(lldb) expr head_bf
(node *) $14 = 0x0000000101000000
(lldb) expr head_bf->next
(node_struct *) $15 = 0x0000000000000000
(lldb) expr head_bf->prev
error: no member named 'prev' in 'node_struct'
error: 1 errors parsing expression
(lldb) expr head_bf->previous
(node_struct *) $16 = 0x0000000000000000
(lldb) expr head_bf->size
(int) $17 = 8192
(lldb) expr head_bf->is_allocated
(int) $18 = 0
(lldb) bt
* thread #1: tid = 0x25006, 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0xffffffffffffffec)
    frame #0: 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105
    frame #1: 0x0000000100001275 main_test.out`best_fit_dealloc(ptr=0x0000000000000000) + 21 at mem.c:138
    frame #2: 0x0000000100001412 main_test.out`mem_dealloc_test(ptr=0x0000000000000000, algo=0) + 34 at main_test.c:39
  * frame #3: 0x0000000100001547 main_test.out`test_not_split_easy(algo=0) + 215 at main_test.c:66
    frame #4: 0x0000000100001e56 main_test.out`main(argc=2, argv=0x00007fff5fbff648) + 230 at main_test.c:170
    frame #5: 0x00007fffc67ca235 libdyld.dylib`start + 1
    frame #6: 0x00007fffc67ca235 libdyld.dylib`start + 1
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) break mem.c:25
error: command 'breakpoint' did not recognize 'mem .c:25' as valid (subcommand might be invalid).
ambiguous command 'break'. Possible completions:
	breakpoint
(lldb) breakpoint
The following subcommands are supported:

      clear   -- Clears a breakpoint or set of breakpoints in the executable.
      command -- A set of commands for adding, removing and examining bits of
                 code to be executed when the breakpoint is hit (breakpoint
                 'commands').
      delete  -- Delete the specified breakpoint(s).  If no breakpoints are
                 specified, delete them all.
      disable -- Disable the specified breakpoint(s) without removing them.  If
                 none are specified, disable all breakpoints.
      enable  -- Enable the specified disabled breakpoint(s). If no breakpoints
                 are specified, enable all of them.
      list    -- List some or all breakpoints at configurable levels of detail.
      modify  -- Modify the options on a breakpoint or set of breakpoints in
                 the executable.  If no breakpoint is specified, acts on the
                 last created breakpoint.  With the exception of -e, -d and -i,
                 passing an empty argument clears the modification.
      name    -- A set of commands to manage name tags for breakpoints
      set     -- Sets a breakpoint or set of breakpoints in the executable.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) breakpoint set
error: invalid combination of options for the given command
(lldb) breakpoint set mem.c:25
error: invalid combination of options for the given command
(lldb) help breakpoint set
     Sets a breakpoint or set of breakpoints in the executable.

Syntax: breakpoint set <cmd-options>

Command Options Usage:
  breakpoint set [-DHo] -l <linenum> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-K <boolean>] [-N <breakpoint-name>] [-m <boolean>]
  breakpoint set [-DHo] -a <address-expression> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-N <breakpoint-name>]
  breakpoint set [-DHo] -n <function-name> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-L <language>] [-K <boolean>] [-N <breakpoint-name>]
  breakpoint set [-DHo] -F <fullname> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-L <language>] [-K <boolean>] [-N <breakpoint-name>]
  breakpoint set [-DHo] -S <selector> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-L <language>] [-K <boolean>] [-N <breakpoint-name>]
  breakpoint set [-DHo] -M <method> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-L <language>] [-K <boolean>] [-N <breakpoint-name>]
  breakpoint set [-DHo] -r <regular-expression> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-L <language>] [-K <boolean>] [-N <breakpoint-name>]
  breakpoint set [-DHo] -b <function-name> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-L <language>] [-K <boolean>] [-N <breakpoint-name>]
  breakpoint set [-ADHo] -p <regular-expression> [-s <shlib-name>] [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-f <filename>] [-N <breakpoint-name>] [-m <boolean>]
  breakpoint set [-DHo] -E <language> [-i <count>] [-c <expr>] [-x <thread-index>] [-t <thread-id>] [-T <thread-name>] [-q <queue-name>] [-w <boolean>] [-h <boolean>] [-O <type-name>] [-N <breakpoint-name>]

       -A ( --all-files )
            All files are searched for source pattern matches.

       -D ( --dummy-breakpoints )
            Sets Dummy breakpoints - i.e. breakpoints set before a file is
            provided, which prime new targets.

       -E <language> ( --language-exception <language> )
            Set the breakpoint on exceptions thrown by the specified language
            (without options, on throw but not catch.)

       -F <fullname> ( --fullname <fullname> )
            Set the breakpoint by fully qualified function names. For C++ this
            means namespaces and all arguments, and for Objective C this means
            a full function prototype with class and selector.  Can be repeated
            multiple times to make one breakpoint for multiple names.

       -H ( --hardware )
            Require the breakpoint to use hardware breakpoints.

       -K <boolean> ( --skip-prologue <boolean> )
            sKip the prologue if the breakpoint is at the beginning of a
            function.  If not set the target.skip-prologue setting is used.

       -L <language> ( --language <language> )
            Specifies the Language to use when interpreting the breakpoint's
            expression (note: currently only implemented for setting
            breakpoints on identifiers).  If not set the target.language
            setting is used.

       -M <method> ( --method <method> )
            Set the breakpoint by C++ method names.  Can be repeated multiple
            times to make one breakpoint for multiple methods.

       -N <breakpoint-name> ( --breakpoint-name <breakpoint-name> )
            Adds this to the list of names for this breakopint.

       -O <type-name> ( --exception-typename <type-name> )
            The breakpoint will only stop if an exception Object of this type
            is thrown.  Can be repeated multiple times to stop for multiple
            object types.  If you just specify the type's base name it will
            match against that type in all modules, or you can specify the full
            type name including modules.  Other submatches are not supported at
            present.Only supported for Swift at present.

       -S <selector> ( --selector <selector> )
            Set the breakpoint by ObjC selector name. Can be repeated multiple
            times to make one breakpoint for multiple Selectors.

       -T <thread-name> ( --thread-name <thread-name> )
            The breakpoint stops only for the thread whose thread name matches
            this argument.

       -a <address-expression> ( --address <address-expression> )
            Set the breakpoint at the specified address.  If the address maps
            uniquely to a particular binary, then the address will be converted
            to a "file" address, so that the breakpoint will track that
            binary+offset no matter where the binary eventually loads.
            Alternately, if you also specify the module - with the -s option -
            then the address will be treated as a file address in that module,
            and resolved accordingly.  Again, this will allow lldb to track
            that offset on subsequent reloads.  The module need not have been
            loaded at the time you specify this breakpoint, and will get
            resolved when the module is loaded.

       -b <function-name> ( --basename <function-name> )
            Set the breakpoint by function basename (C++ namespaces and
            arguments will be ignored). Can be repeated multiple times to make
            one breakpoint for multiple symbols.

       -c <expr> ( --condition <expr> )
            The breakpoint stops only if this condition expression evaluates to
            true.

       -f <filename> ( --file <filename> )
            Specifies the source file in which to set this breakpoint.  Note,
            by default lldb only looks for files that are #included if they use
            the standard include file extensions.  To set breakpoints on
            .c/.cpp/.m/.mm files that are #included, set
            target.inline-breakpoint-strategy to "always".

       -h <boolean> ( --on-catch <boolean> )
            Set the breakpoint on exception catcH.

       -i <count> ( --ignore-count <count> )
            Set the number of times this breakpoint is skipped before stopping.

       -l <linenum> ( --line <linenum> )
            Specifies the line number on which to set this breakpoint.

       -m <boolean> ( --move-to-nearest-code <boolean> )
            Move breakpoints to nearest code. If not set the
            target.move-to-nearest-code setting is used.

       -n <function-name> ( --name <function-name> )
            Set the breakpoint by function name.  Can be repeated multiple
            times to make one breakpoint for multiple names

       -o ( --one-shot )
            The breakpoint is deleted the first time it causes a stop.

       -p <regular-expression> ( --source-pattern-regexp <regular-expression> )
            Set the breakpoint by specifying a regular expression which is
            matched against the source text in a source file or files specified
            with the -f option.  The -f option can be specified more than once.
            If no source files are specified, uses the current "default source
            file"

       -q <queue-name> ( --queue-name <queue-name> )
            The breakpoint stops only for threads in the queue whose name is
            given by this argument.

       -r <regular-expression> ( --func-regex <regular-expression> )
            Set the breakpoint by function name, evaluating a
            regular-expression to find the function name(s).

       -s <shlib-name> ( --shlib <shlib-name> )
            Set the breakpoint only in this shared library.  Can repeat this
            option multiple times to specify multiple shared libraries.

       -t <thread-id> ( --thread-id <thread-id> )
            The breakpoint stops only for the thread whose TID matches this
            argument.

       -w <boolean> ( --on-throw <boolean> )
            Set the breakpoint on exception throW.

       -x <thread-index> ( --thread-index <thread-index> )
            The breakpoint stops only for the thread whose indeX matches this
            argument.
(lldb) breakpoint set -l
lldb: option requires an argument -- l
error: unknown or ambiguous option
(lldb) breakpoint set -l 25
Breakpoint 1: where = main_test.out`memory_init_test + 42 at main_test.c:25, address = 0x000000010000138a
(lldb) quit
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) run
Process 2714 launched: './main_test.out' (x86_64)
Process 2714 stopped
* thread #1: tid = 0x25f33, 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0xffffffffffffffec)
    frame #0: 0x00000001000010ac main_test.out`mem_dealloc(ptr=0x0000000000000000) + 28 at mem.c:105
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
   104 		node* current = (node*) ((void*)ptr - (void*)sizeof(node));
-> 105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
   108 		int previous_free = current->previous && !(current->previous->is_allocated);
(lldb) expr ptr
(void *) $0 = 0x0000000000000000
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF mem.d mem.c
gcc -Wall -g -c mem.c
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) run
Process 2748 launched: './main_test.out' (x86_64)
test_not_split_easy: 1111
test_not_split_hard: 1 1 1 1
test_left_deallocate: 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 0 0 0 1
test_right_deallocate: 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 0 1 0 0 0 1
Process 2748 exited with status = 0 (0x00000000)
(lldb) breakpoint set -l 105
Breakpoint 1: where = main_test.out`test_left_deallocate + 551 at main_test.c:105, address = 0x0000000100001877
(lldb) run
Process 2771 launched: './main_test.out' (x86_64)
test_not_split_easy: 1111
test_not_split_hard: 1 1 1 1
Process 2771 stopped
* thread #1: tid = 0x26965, 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105
   102 		printf("%d ", head->previous == NULL);
   103
   104 		mem_dealloc_test(mem, algo);
-> 105 		printf("%d ", head->is_allocated == 0);
   106 		printf("%d ", head->next != NULL);
   107 		printf("%d ", head->next->size == 1024 - sizeof(node));
   108 		printf("%d ", head->next->is_allocated == 1);
(lldb) expr head
(node *) $0 = 0x0000000100801000
(lldb) expr head->is_allocated
(int) $1 = 1
(lldb) expr head->next->is_allocated
(int) $2 = 1
(lldb) expr head->next->size
(int) $3 = 1000
(lldb) expr head->size
(int) $4 = 7168
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF mem.d mem.c
gcc -Wall -g -c mem.c
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) run
Process 2809 launched: './main_test.out' (x86_64)
test_not_split_easy: 1111
test_not_split_hard: 1 1 1 1
test_left_deallocate: 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 0 0 0 1
test_right_deallocate: 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 0 1 0 0 0 1
Process 2809 exited with status = 0 (0x00000000)
(lldb) breakpoint set -l 105
Breakpoint 1: where = main_test.out`test_left_deallocate + 551 at main_test.c:105, address = 0x0000000100001877
(lldb) run
Process 2813 launched: './main_test.out' (x86_64)
test_not_split_easy: 1111
test_not_split_hard: 1 1 1 1
Process 2813 stopped
* thread #1: tid = 0x26e0d, 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105
   102 		printf("%d ", head->previous == NULL);
   103
   104 		mem_dealloc_test(mem, algo);
-> 105 		printf("%d ", head->is_allocated == 0);
   106 		printf("%d ", head->next != NULL);
   107 		printf("%d ", head->next->size == 1024 - sizeof(node));
   108 		printf("%d ", head->next->is_allocated == 1);
(lldb) expr head->is_allocated
(int) $0 = 1
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) breakpoint set -l 105
Breakpoint 1: where = main_test.out`test_left_deallocate + 551 at main_test.c:105, address = 0x0000000100001877
(lldb) run
Process 2840 launched: './main_test.out' (x86_64)
test_not_split_easy: 1111
test_not_split_hard: 1 1 1 1
Process 2840 stopped
* thread #1: tid = 0x26f70, 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105
   102 		printf("%d ", head->previous == NULL);
   103
   104 		mem_dealloc_test(mem, algo);
-> 105 		printf("%d ", head->is_allocated == 0);
   106 		printf("%d ", head->next != NULL);
   107 		printf("%d ", head->next->size == 1024 - sizeof(node));
   108 		printf("%d ", head->next->is_allocated == 1);
(lldb) f v
error: invalid frame index argument 'v'
(lldb) f vs
error: invalid frame index argument 'vs'
(lldb) f variables
error: invalid frame index argument 'variables'
(lldb) frame variables
invalid command 'frame variables'.
(lldb) frame
The following subcommands are supported:

      info     -- List information about the currently selected frame in the
                  current thread.
      select   -- Select a frame by index from within the current thread and
                  make it the current frame.
      variable -- Show frame variables. All argument and local variables that
                  are in scope will be shown when no arguments are given. If
                  any arguments are specified, they can be names of argument,
                  local, file static and file global variables. Children of
                  aggregate variables can be specified such as 'var->child.x'.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) frame var
(int) algo = 0
(void *) mem = 0x0000000101000240
(node *) head = 0x0000000101000000
(void *) mem2 = 0x000000010102a480
(lldb) bt
* thread #1: tid = 0x26f70, 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
  * frame #0: 0x0000000100001877 main_test.out`test_left_deallocate(algo=0) + 551 at main_test.c:105
    frame #1: 0x0000000100001e66 main_test.out`main(argc=2, argv=0x00007fff5fbff648) + 246 at main_test.c:172
    frame #2: 0x00007fffc67ca235 libdyld.dylib`start + 1
    frame #3: 0x00007fffc67ca235 libdyld.dylib`start + 1
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) breakpoint set -l 104 -f mem.c
Breakpoint 1: where = main_test.out`mem_dealloc + 12 at mem.c:104, address = 0x000000010000109c
(lldb) breakpoint set -l 105
Breakpoint 2: where = main_test.out`test_left_deallocate + 551 at main_test.c:105, address = 0x0000000100001877
(lldb) run
Process 2846 launched: './main_test.out' (x86_64)
Process 2846 stopped
* thread #1: tid = 0x27223, 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104
   101 	//---------------------------------------------------//
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
-> 104 		node* current = (node*) ((void*)ptr - sizeof(node));
   105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
(lldb) bt
* thread #1: tid = 0x27223, 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
  * frame #0: 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104
    frame #1: 0x0000000100001275 main_test.out`best_fit_dealloc(ptr=0x0000000101000240) + 21 at mem.c:138
    frame #2: 0x0000000100001412 main_test.out`mem_dealloc_test(ptr=0x0000000101000240, algo=0) + 34 at main_test.c:39
    frame #3: 0x0000000100001547 main_test.out`test_not_split_easy(algo=0) + 215 at main_test.c:66
    frame #4: 0x0000000100001e56 main_test.out`main(argc=2, argv=0x00007fff5fbff648) + 230 at main_test.c:170
    frame #5: 0x00007fffc67ca235 libdyld.dylib`start + 1
    frame #6: 0x00007fffc67ca235 libdyld.dylib`start + 1
(lldb) continue
Process 2846 resuming
test_not_split_easy: 1111
Process 2846 stopped
* thread #1: tid = 0x27223, 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104
   101 	//---------------------------------------------------//
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
-> 104 		node* current = (node*) ((void*)ptr - sizeof(node));
   105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
(lldb) bt
* thread #1: tid = 0x27223, 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
  * frame #0: 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104
    frame #1: 0x0000000100001275 main_test.out`best_fit_dealloc(ptr=0x0000000101000240) + 21 at mem.c:138
    frame #2: 0x0000000100001412 main_test.out`mem_dealloc_test(ptr=0x0000000101000240, algo=0) + 34 at main_test.c:39
    frame #3: 0x0000000100001637 main_test.out`test_not_split_hard(algo=0) + 215 at main_test.c:80
    frame #4: 0x0000000100001e5e main_test.out`main(argc=2, argv=0x00007fff5fbff648) + 238 at main_test.c:171
    frame #5: 0x00007fffc67ca235 libdyld.dylib`start + 1
    frame #6: 0x00007fffc67ca235 libdyld.dylib`start + 1
(lldb) continue
Process 2846 resuming
test_not_split_hard: 1 1 1 1
Process 2846 stopped
* thread #1: tid = 0x27223, 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104
   101 	//---------------------------------------------------//
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
-> 104 		node* current = (node*) ((void*)ptr - sizeof(node));
   105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
(lldb) bt
* thread #1: tid = 0x27223, 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
  * frame #0: 0x000000010000109c main_test.out`mem_dealloc(ptr=0x0000000101000240) + 12 at mem.c:104
    frame #1: 0x0000000100001275 main_test.out`best_fit_dealloc(ptr=0x0000000101000240) + 21 at mem.c:138
    frame #2: 0x0000000100001412 main_test.out`mem_dealloc_test(ptr=0x0000000101000240, algo=0) + 34 at main_test.c:39
    frame #3: 0x0000000100001870 main_test.out`test_left_deallocate(algo=0) + 544 at main_test.c:104
    frame #4: 0x0000000100001e66 main_test.out`main(argc=2, argv=0x00007fff5fbff648) + 246 at main_test.c:172
    frame #5: 0x00007fffc67ca235 libdyld.dylib`start + 1
    frame #6: 0x00007fffc67ca235 libdyld.dylib`start + 1
(lldb) frame
The following subcommands are supported:

      info     -- List information about the currently selected frame in the
                  current thread.
      select   -- Select a frame by index from within the current thread and
                  make it the current frame.
      variable -- Show frame variables. All argument and local variables that
                  are in scope will be shown when no arguments are given. If
                  any arguments are specified, they can be names of argument,
                  local, file static and file global variables. Children of
                  aggregate variables can be specified such as 'var->child.x'.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) thread
The following subcommands are supported:

      backtrace      -- Show the stack for one or more threads.  If no threads
                        are specified, show the currently selected thread.  Use
                        the thread-index "all" to see all threads.
      continue       -- Continue execution of one or more threads in an active
                        process.
      info           -- Show an extended summary of information about thread(s)
                        in a process.
      jump           -- Sets the program counter to a new address.
      list           -- Show a summary of all current threads in a process.
      plan           -- A set of subcommands for accessing the thread plans
                        controlling execution control on one or more threads.
      return         -- Return from the currently selected frame,
                        short-circuiting execution of the frames below it, with
                        an optional return value, or with the -x option from
                        the innermost function evaluation.  This command takes
                        'raw' input (no need to quote stuff).
      select         -- Select a thread as the currently active thread.
      step-in        -- Source level single step in specified thread (current
                        thread, if none specified).
      step-inst      -- Single step one instruction in specified thread
                        (current thread, if none specified).
      step-inst-over -- Single step one instruction in specified thread
                        (current thread, if none specified), stepping over
                        calls.
      step-out       -- Finish executing the function of the currently selected
                        frame and return to its call site in specified thread
                        (current thread, if none specified).
      step-over      -- Source level single step in specified thread (current
                        thread, if none specified), stepping over calls.
      step-scripted  -- Step as instructed by the script class passed in the -C
                        option.
      until          -- Run the current or specified thread until it reaches a
                        given line number or address or leaves the current
                        function.

For more help on any particular subcommand, type 'help <command> <subcommand>'.
(lldb) thread step-in
Process 2846 stopped
* thread #1: tid = 0x27223, 0x00000001000010a8 main_test.out`mem_dealloc(ptr=0x0000000101000240) + 24 at mem.c:105, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x00000001000010a8 main_test.out`mem_dealloc(ptr=0x0000000101000240) + 24 at mem.c:105
   102 	void mem_dealloc(void *ptr) {
   103 		// makes sure to get the node pointer of the header and not the memory
   104 		node* current = (node*) ((void*)ptr - sizeof(node));
-> 105 		current->is_allocated = 0; // also 1) nothing is free around me
   106
   107 		// gets the previous and next node
   108 		int previous_free = current->previous && !(current->previous->is_allocated);
(lldb) expr current
(node *) $0 = 0x0000000101000228
(lldb) expr head
warning: could not load any Objective-C class information. This will significantly reduce the quality of type information available.
error: use of undeclared identifier 'head'
error: 1 errors parsing expression
(lldb) expr head_bf
(node *) $1 = 0x0000000101000000
(lldb) expr head_wf
(node *) $2 = 0x0000000000000000
(lldb) expr ptr
(void *) $3 = 0x0000000101000240
(lldb) quit
Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] y
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ make
gcc -MM -MF mem.d mem.c
gcc -Wall -g -c mem.c
gcc -o main_test.out mem.o main_test.o  -g
anasant@v1022-rn-113-184:~/Documents/repos/ece-254/ece254-labs/lab4-student/starter$ lldb -- ./main_test.out 0
(lldb) target create "./main_test.out"
Current executable set to './main_test.out' (x86_64).
(lldb) settings set -- target.run-args  "0"
(lldb) run
Process 2877 launched: './main_test.out' (x86_64)
test_not_split_easy: 1111
test_not_split_hard: 1 1 1 1
test_left_deallocate: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Process 2877 stopped
* thread #1: tid = 0x278e4, 0x00000001000011d9 main_test.out`mem_dealloc(ptr=0x0000000101000018) + 329 at mem.c:124, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x10)
    frame #0: 0x00000001000011d9 main_test.out`mem_dealloc(ptr=0x0000000101000018) + 329 at mem.c:124
   121 		else if (!previous_free && next_free) {
   122 			current->size += current->next->size + sizeof(node);
   123 			current->next = current->next->next;
-> 124 			current->next->previous = current;
   125 		}
   126 		// 4) both previous and next spaces are free
   127 		else if (previous_free && next_free) {
(lldb)