#ifndef CKYLARK_TAG_SET_H_
#define CKYLARK_TAG_SET_H_

#include <ckylark/Dictionary.h>
#include <ckylark/Tree.h>
#include <ckylark/Stream.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Ckylark {

class TagSet {

    TagSet();
    TagSet(const TagSet &) = delete;
    TagSet & operator=(const TagSet &) = delete;

public:
    ~TagSet();

    static std::shared_ptr<TagSet> loadFromStream(InputStream & stream);

    int getTagId(std::string name) const { return tag_table_.getId(name); }
    std::string getTagName(int id) const { return tag_table_.getWord(id); }

    inline size_t getDepth() const { return depth_; }
    inline size_t numTags() const { return tree_list_.size(); }
    inline size_t numSubtags(int tag_id, int level) const { return num_subtags_[tag_id][level]; };

    const Tree<int> & getSubtagTree(int tag_id) const { return *tree_list_[tag_id]; }

private:
    size_t depth_;
    Dictionary tag_table_;
    std::vector<Tree<int> *> tree_list_;
    std::vector<std::vector<size_t> > num_subtags_;

    static Tree<int> * makeSubtagTree(const std::vector<std::string> & tok, int & pos);

    void checkDepth();
    static size_t getDepthByNode(Tree<int> & node);
    //static size_t numSubtagsByNode(Tree<int> & node, int rest_depth);

}; // class TagSet

} // namespace Ckylark

#endif // CKYLARK_TAG_SET_H_

