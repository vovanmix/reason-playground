let def: Types.address = {street: "", zip: 0};

let renderItem = (item, onChange) => <Address address=item onChange />;

let make = (~addresses: list(Types.address), ~onChange, _children) =>
  GenericList.genericList(
    ~items=addresses,
    ~onChange,
    ~label="Addresses",
    ~defaultValue=def,
    ~renderItem
  );
