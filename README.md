# xd

Hex Dumper

## How to use

Build from the checked out directory
```
$ make all
```

Run the executable in the following fashion
```
$ ./build/xd [ OPTIONS ] [ FILE [ FILE [ FILE ... ] ] ]
```
or
```
$ ./build/xd -
```

| Option                              | Description                                             |
|-------------------------------------|---------------------------------------------------------|
| -h                                  | print out this help menu and quit                       |
| -b\<NUM\>, --bytes-per-line=\<NUM\> | number of bytes to display per line (default: 16)       |
| -l\<NUM\>, --lines-per-read=\<NUM\> | number of lines per read (default: 512)                 |
| -O\<NUM\>, --offset=\<NUM\>         | number of bytes to skip from the beginning (default: 0) |
| -L\<NUM\>, --limit=\<NUM\>          | number of bytes to dump (default: 0, means no limit)    |

| Notation | Meaning                  |
|----------|--------------------------|
| \<NUM\>  | an integer number        |
| FILE     | path of the file to dump |
| -        | read from stdin          |

## How to install

Copy the resulting executable to anywhere in the PATH.
