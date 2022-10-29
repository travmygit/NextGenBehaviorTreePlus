# NextGenBehaviorTreePlus
UE5! Develop some powerful and useful composite nodes, decorator nodes and task nodes to extend the ability of Behavior Tree.

## New Composites
### Random Selector
**Random Selector** Nodes select randomly from their children to execute. They stop executing despite any of their children succeeds of fails.
| Property              | Description                                                                                                                                  |
|-----------------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| Apply decorator Scope | If set, all Decorators in the branch below will be removed when execution flow leaves the branch (Decorators on this node are not affected). |
| Node Name             | The name the node should display in the Behavior Tree graph.                                                                                 |
| Weights               | Weights of children when the node is using weight random algorithm.                                                                          |
| bUseWeights           | The node will ues weight random algorithm to select from its children (by default, each of the children has the same possibility).           |
