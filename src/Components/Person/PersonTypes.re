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

module Decode = {
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
  /* TODO: decide; Axios returns a JS type, Fetch returns a string */
  /* let address = json =>
       Json.Decode.{
         street: json |> field("street", string),
         zip: json |> field("zip", int)
       };
     let addresses = json => Json.Decode.(json |> list(address));
     let person = json =>
       Json.Decode.{
         id: json |> optional(field("id", int)),
         country: json |> field("country", int),
         name: json |> field("name", string),
         enabled: json |> field("enabled", bool),
         addresses: json |> field("addresses", addresses),
         file: json |> optional(field("file", string)),
         created_at: json |> optional(field("created_at", string))
       };
     let persons = json => Json.Decode.(json |> list(person)); */
};
