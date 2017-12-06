open BsReactNative;

type _state = {mutable elementRef: option ReasonReact.reactRef};

let setRef theRef {ReasonReact.state: state} => state.elementRef = Js.Null.to_opt theRef;

let styles =
  StyleSheet.create
    Style.(
      {
        "item":
          style [
            flex 1.,
            backgroundColor "rgb(75, 118, 134)",
            marginHorizontal 10.,
            marginTop 10.,
            borderWidth 1.,
            borderColor "rgb(137, 167, 177)"
          ],
        "row": style [flexDirection `row],
        "titleWrap": style [flex 1., padding 10.]
      }
    );

let component = ReasonReact.statefulComponent "TalkItem";

let make
    item::({Item.start: start} as item)
    talk::({Item.talkTitle: talkTitle} as talk)
    index::(index: int)
    modalOpen::(modalOpen: bool)
    selectedIndex::(selectedIndex: int)
    ::onPress
    _children => {
  ...component,
  initialState: fun () => {elementRef: None},
  render: fun self =>
    <TouchableOpacity
      onPress=(
        fun _ =>
          switch self.state.elementRef {
          | None => ()
          | Some r =>
            (ReasonReact.refToJsObj r)##measureInWindow (
              fun x y width height => onPress (x, y, width, height, item, index)
            )
          }
      )>
      <View
        style=Style.(
                concat [
                  styles##item,
                  style [opacity (modalOpen && index === selectedIndex ? 0. : 1.)]
                ]
              )
        ref=(self.handle setRef)>
        <View style=styles##row>
          <View style=styles##titleWrap> <ScheduleTitle talkTitle /> <SpeakerNames talk /> </View>
          <SpeakerImages talk />
        </View>
        <ScheduleTime start />
      </View>
    </TouchableOpacity>
};
