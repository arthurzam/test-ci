#!/usr/bin/env python3

from http.client import HTTPSConnection
import sys
from typing import Iterator, NamedTuple
from urllib.parse import quote_plus
import xml.etree.ElementTree as ET


class Maintainer(NamedTuple):
    name: str
    email: str

    def check_details(self, client: HTTPSConnection) -> bool:
        try:
            client.request("GET", f"/rest/user?names={quote_plus(self.email)}")
            resp = client.getresponse()
            resp.read()
            return resp.status == 200
        except Exception:
            return False


def read_repositories(file: str) -> Iterator[Maintainer]:
    tree = ET.parse(file)
    for maintainer in tree.findall('./repo/owner'):
        values = {child.tag: child.text for child in maintainer}
        yield Maintainer(name=values.get('name', ''), email=values.get('email', ''))


def check_maintainers(maintainers: Iterator[Maintainer]) -> Iterator[Maintainer]:
    try:
        client = HTTPSConnection('bugs.gentoo.org')
        for m in maintainers:
            if m.check_details(client):
                print(f'\033[92m\u2713 {m.name} <{m.email}>\033[0m')
            else:
                print(f'\033[91m\u2717 {m.name} <{m.email}>\033[0m')
                yield m
    finally:
        client.close()


if __name__ == '__main__':
    base = set(read_repositories(sys.argv[1]))
    current = set(read_repositories(sys.argv[2]))
    missing_maintainers = len(tuple(check_maintainers(current - base)))
    sys.exit(int(missing_maintainers != 0))
