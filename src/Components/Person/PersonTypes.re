type person = {
  id: option(int),
  country: int,
  name: string,
  enabled: bool,
  addresses: list(address),
  file: option(string),
  created_at: option(string)
}
and address = {
  street: string,
  zip: int
};

type jsonPerson = {
  .
  "id": Js.Nullable.t(int),
  "country": int,
  "name": string,
  "enabled": Js.boolean,
  "addresses": array(jsonAddress),
  "file": Js.Nullable.t(string),
  "created_at": Js.Nullable.t(string)
}
and jsonAddress = {
  .
  "street": string,
  "zip": int
};

module Decode = {
  let address = (json: jsonAddress) => {street: json##street, zip: json##zip};
  let person = (json: jsonPerson) => {
    id: json##id |> Js.Nullable.to_opt,
    country: json##country,
    name: json##name,
    enabled: json##enabled |> Js.to_bool,
    addresses: json##addresses |> Array.map(address) |> ArrayLabels.to_list,
    file: json##file |> Js.Nullable.to_opt,
    created_at: json##created_at |> Js.Nullable.to_opt
  };
  let persons = (json: array(jsonPerson)) =>
    json |> Array.map(person) |> ArrayLabels.to_list;
};

module Encode = {
  let address = (record: address) : jsonAddress => {
    "street": record.street,
    "zip": record.zip
  };
  let person = (record: person) : jsonPerson => {
    "id": record.id |> Js.Nullable.from_opt,
    "country": record.country,
    "name": record.name,
    "enabled": record.enabled |> Js.Boolean.to_js_boolean,
    "addresses": record.addresses |> List.map(address) |> ArrayLabels.of_list,
    "file": record.file |> Js.Nullable.from_opt,
    "created_at": record.created_at |> Js.Nullable.from_opt
  };
};
