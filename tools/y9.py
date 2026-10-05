from io import BytesIO
from struct import unpack, pack
from json import dumps, loads
from argparse import ArgumentParser
from pathlib import Path

# Adapted from MCMi460/PokeBound/tools/rePPTXT
class _DataStream(BytesIO):
    def __init__(self, *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)

    def read(self) -> int:
        return unpack("<I", super().read(4))[0]
    def write(self, var: int) -> None:
        super().write(pack("<I", var))

class y9:
    class OVL_Entry:
        def load(self, data:_DataStream) -> OVL_Entry:
            self.index = data.read()
            self.ram_address = data.read()
            self.size = data.read()
            self.bss_size = data.read()
            self.static_initializer_start_address = data.read()
            self.static_initializer_end_address = data.read()
            self.fs_file_id = data.read()
            self.compressed_hashed_size = data.read()
                # 0xAABBBBBB
                # AA = 02 (uncompressed), 03 (compressed)
                # BBBBBB = size of compressed file, 0 for uncompressed
            return self

        def dump(self) -> bytes:
            data = _DataStream()
            data.write(self.index)
            data.write(self.ram_address)
            data.write(self.size)
            data.write(self.bss_size)
            data.write(self.static_initializer_start_address)
            data.write(self.static_initializer_end_address)
            data.write(self.fs_file_id)
            data.write(self.compressed_hashed_size)
            return data.getvalue()

    def __init__(self, file:Path = None) -> None:
        self.ovl_entries:list[OVL_Entry] = []

        # Initialize overlay table
        if file is not None:
            self.load(file)

    def extract_entry(self, index:int) -> y9.OVL_Entry | None:
        for entry in self.ovl_entries:
            if entry.index == index:
                self.ovl_entries.remove(entry)
                return entry
        return None

    def load(self, file:Path) -> None:
        if file.suffix == ".bin":
            with open(file, "rb") as fd:
                while block := fd.read(32):
                    ovl_entry = y9.OVL_Entry().load(_DataStream(block))
                    self.extract_entry(ovl_entry.index)
                    self.ovl_entries.append(ovl_entry)
        elif file.suffix == ".json":
            with open(file, "r") as fd:
                for entry in loads(fd.read()):
                    ovl_entry = y9.OVL_Entry()
                    for key, value in entry.items():
                        ovl_entry.__dict__[key] = value
                    self.extract_entry(ovl_entry.index)
                    self.ovl_entries.append(ovl_entry)
        else:
            raise ValueError("file type %s is not supported" % file.suffix)

        # Sort our entries
        self.ovl_entries.sort(key = lambda x: x.index)

    def deserialize(self, dest:Path) -> None:
        json_table = []
        for ovl_entry in self.ovl_entries:
            entry_dict = {}
            for key, value in ovl_entry.__dict__.items():
                if not key.startswith("_"):
                    entry_dict[key] = value
            json_table.append(entry_dict)

        with open(dest, "w+") as fd:
            fd.write(dumps(json_table, indent = 4))

    def dump(self, dest:Path) -> None:
        with open(dest, "wb+") as fd:
            fd.write(b"".join(entry.dump() for entry in self.ovl_entries))

if __name__ == "__main__":
    parser = ArgumentParser(description = "y9 (de)serializer")

    parser.add_argument(
        "-i", "--input", 
        type = str,
        required = True,
        action = "append",
        help = "path to input y9(s) (.json/.bin) - will merge if multiple supplied\n" +
               "(later inputs are prioritized)"
    )
    parser.add_argument(
        "-o", "--output", 
        type = str,
        required = True,
        help = "path to output y9 (.json/.bin)"
    )

    args = parser.parse_args()

    in_paths = [ Path(path) for path in args.input ]
    out_path = Path(args.output)
    assert all(path.is_file() for path in in_paths)

    obj = y9()
    for path in in_paths:
        obj.load(path)

    if out_path.suffix == ".json":
        obj.deserialize(out_path)
    elif out_path.suffix == ".bin":
        obj.dump(out_path)
    else:
        raise ValueError("unknown destination file type\n" +
            "(cannot determine function to apply: serialize or deserialize)")
