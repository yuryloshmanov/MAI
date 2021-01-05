class Person:
    """
    Представление персоны генеалогического дерева.
    Свойства: идентификатор, имя, фамилия, пол и идентификатор семьи.
    """

    def __init__(self):
        self.id = ""
        self.name = ""
        self.surname = ""
        self.sex = ""
        self.family_id = ""

    def parse(self, buff):
        for row in buff:
            if row[0] == "0":
                self.id = row[1][2:len(row[1]) - 1]
            elif row[1] == "GIVN":
                self.name = row[2]
            elif row[1] == "SURN":
                self.surname = row[2]
            elif row[1] == "_MARNM":
                self.surname = row[2]
            elif row[1] == "SEX":
                self.sex = row[2].lower()
            elif row[1] == "FAMS":
                self.family_id = row[2][2:len(row[2]) - 1]
            elif row[1] == "FAMC" and self.family_id == "":
                self.family_id = row[2][2:len(row[2]) - 1]


class Family:
    """
    Представление семьи в генеалогическом дереве.
    Свойства: идентификатор семьи, идентификатор мужа, идентификатор жены и список идентификаторов детей.
    Метод parse заполняет все свойства класса из списка.
    Без данного класса нельзя добавить предикаты родства в семье с несколкими детьми.
    """

    def __init__(self):
        self.id = ""
        self.husband_id = ""
        self.wife_id = ""
        self.children_ids = []

    def parse(self, buff):
        for row in buff:
            if row[0] == "0":
                self.id = row[1][2:len(row[1]) - 1]
            elif row[1] == "HUSB":
                self.husband_id = row[2][2:len(row[2]) - 1]
            elif row[1] == "WIFE":
                self.wife_id = row[2][2:len(row[2]) - 1]
            elif row[1] == "CHIL":
                self.children_ids.append(row[2][2:len(row[2]) - 1])


def parse_file(input_file):
    """
    Парсит файл на два списка: персоны и семья.
    """

    persons = []
    families = []
    buff = []
    fam = False
    flag = False

    for line in input_file:
        row = line.split()
        if not fam:
            if row[0] == "0" and row[1][0] == "@" and row[2] == "INDI":
                flag = True
                buff.append(row)
            elif row[0] == "0" and row[1][0] == "@" and row[2] == "FAM":
                fam = True
                buff.append(row)
            elif flag:
                buff.append(row)
                if row[0] == "1" and row[1] == "_UID":
                    p = Person()
                    p.parse(buff)
                    persons.append(p)
                    buff = []
                    flag = False
        else:
            buff.append(row)
            if row[0] == "1" and row[1] == "_UID":
                fam = Family()
                fam.parse(buff)
                families.append(fam)
                buff = []
                fam = False

    return persons, families


def write_prolog_program(output_file, families, persons):
    """
    Записывает предикаты в .pl файл в соотвествие со II вариантом(parent(родитель, ребенок), sex(человек, m/f)).
    """

    def find_person(person_id) -> Person:
        for person in persons:
            if person.id == person_id:
                return person

    for family in families:
        for child_id in family.children_ids:
            father = find_person(family.husband_id)
            mother = find_person(family.wife_id)
            child = find_person(child_id)
            output_file.write(f"parent('{father.name} {father.surname}', '{child.name} {child.surname}').\n")
            output_file.write(f"parent('{mother.name} {mother.surname}', '{child.name} {child.surname}').\n")

    output_file.write("\n")
    for person in persons:
        output_file.write(f"sex('{person.name} {person.surname}', {person.sex}).\n")


def main():
    input_file = open("heritage.ged", "r")
    output_file = open("heritage.pl", "w")
    persons, families = parse_file(input_file)
    write_prolog_program(output_file, families, persons)


if __name__ == "__main__":
    f = open("heritage.ged")
    main()
