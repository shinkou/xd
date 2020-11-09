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
| -h                                  | print out help menu and quit                            |
| -l\<NUM\>, --limit=\<NUM\>          | number of bytes to dump (default: 0, means no limit)    |
| -o\<NUM\>, --offset=\<NUM\>         | number of bytes to skip from the beginning (default: 0) |
| -r\<NUM\>, --read-size=\<NUM\>      | read size, in number of lines (default: 512)            |
| -w\<NUM\>, --width=\<NUM\>          | width, in number of bytes (default: 16)                 |

| Notation | Meaning                  |
|----------|--------------------------|
| \<NUM\>  | an integer number        |
| FILE     | path of the file to dump |
| -        | read from stdin          |

## How to install

Copy the resulting executable to anywhere in the PATH.
